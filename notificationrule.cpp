#include "notificationrule.h"
#include "jenkinsApi/lastsuccesbuildnumber.h"
#include "jenkinsApi/buildstatus.h"
#include "jenkinsApi/changesinfo.h"
#include "settingssingleton.h"

#include <QDomDocument>
#include <QDebug>

NotificationRule::NotificationRule(const NotificationRuleData & nrd, QObject * parent)
    : QObject(parent)
    , m_host (SettingsSingleton::instance().jenkinsUrl())
    , m_data (nrd)
    , m_notifySuccess(false)
    , m_isFailSpree(false)
    , m_lastSuccessApi (new LastSuccesBuildNumber(m_host, m_data.jobName(), this))
    , m_processing(true)

{
    connect(m_lastSuccessApi,SIGNAL(buildNumberReady(int)),this,SLOT(onLastSuccess(int)));
}

NotificationRule::~NotificationRule()
{
    foreach (BuildStatus* st, m_buildStatusApi) {
        delete st;
    }
    m_buildStatusApi.clear();
    foreach (ChangesInfo* ci, m_buildCommitsApi) {
        delete ci;
    }
    m_buildCommitsApi.clear();
}

void NotificationRule::jobStatusReady(int buildNumber, const BuildResult & result)
{
    if(result == noStatus) //This could mean e.g. build is in progress. It should be processed at next polling.
        return;
    if (m_processing) //Rule can check only one build at time.
        return;

    m_processing = true;

    int lastNumber = m_lastBuildNumber;
    m_lastBuildNumber = buildNumber;
    BuildResult lastResult = m_lastResult;
    m_lastResult = result;
    BuildResult lastRevelantResult = m_lastRevelantResult;
    if( resultIsRevelant (result) )
    {
        m_lastRevelantResult = result;
    }

    //ignore if nothing changed
    if(lastNumber == buildNumber || lastResult == result)
        return;

    m_notifySuccess = false;
    if(result == success && lastRevelantResult != success && m_data.notifyEndOfFailSpree()) {
        notify();
        m_processing = false;
        return;
    }
    else if ( (result == failure) && (lastRevelantResult == success) ) {

        if (!m_data.notifyFailures())
            return;
        if (lastNumber + 1 ==  buildNumber)  { //We are on the place of crime. Call for suspects.
            ChangesInfo * chin = new ChangesInfo(m_host, m_data.jobName(), buildNumber);
            connect (chin, SIGNAL(changeListReady(int, const QList<ChangeItem> &)),
                     this, SLOT(failingBuildChanges(int, const QList<ChangeItem> &)));
            chin->fetchData(buildNumber);
            m_buildCommitsApi.insert(buildNumber, chin);
            return;

        }
        else {
            //We have to find first failing build. We starting search after last success.
            //All committers between last success and first failure of spree are also suspected.
            m_lastSuccessApi->fetchData();
        }
    }

}

void NotificationRule::failingBuildChanges(int buildNumber, const QList<ChangeItem> & changes)
{
    m_suspectedChanges.append(changes);
    //Last build where could be cause of fail. End of witch hunting. Notifying what we found.

    bool notificationNeeded = true;
    if(m_data.filterByCommiter()){
         notificationNeeded = false;
        foreach (ChangeItem it, m_suspectedChanges) {
            if(m_data.commiters().contains(it.m_author) ) {
                notificationNeeded = true;
                break;
            }
        }
    }
    if(notificationNeeded)
        notify();

    ChangesInfo * cs = m_buildCommitsApi.value(buildNumber);
    Q_ASSERT(cs);
    m_buildCommitsApi.remove(buildNumber);
    delete cs;
}

void NotificationRule::unsureBuildChanges(int buildNumber, const QList<ChangeItem> & changes)
{
    m_suspectedChanges.append(changes);
    //This build was not failing. We cannot be sure all suspected commits are found.
    checkNextBuild(buildNumber);

    ChangesInfo * cs = m_buildCommitsApi.value(buildNumber);
    Q_ASSERT(cs);
    m_buildCommitsApi.remove(buildNumber);
    delete cs;
}

void NotificationRule::onLastSuccess(int buildNumber)
{
    checkNextBuild(buildNumber);
}

void NotificationRule::checkNextBuild(int buildNumber)
{
    BuildStatus * bust = new BuildStatus(m_host, m_data.jobName(), buildNumber + 1);
    connect (bust, SIGNAL(buildStatusReady(int, const BuildResult &)),
             this, SLOT(suspectedStatusReady(int, const BuildResult &)));
    m_buildStatusApi.insert(buildNumber, bust);
    bust->fetchData();
}

void NotificationRule::notify()
{

}

void NotificationRule::suspectedStatusReady(int buildNumber, const BuildResult & retult)
{
    if (buildNumber < 0) {
        qWarning() << Q_FUNC_INFO << "Invalid build number, stopping processing.";
        m_processing = false;
        return;
    }

    if(!m_processing)
        return;
    Q_ASSERT(buildNumber == m_lastBuildNumber);
    ChangesInfo * chin = new ChangesInfo(m_host, m_data.jobName(), buildNumber);
    if (retult == failure) {
        connect (chin, SIGNAL(changeListReady(int, const QList<ChangeItem> &)),
                 this, SLOT(failingBuildChanges(int, const QList<ChangeItem> &)));
    }
    else {
        connect (chin, SIGNAL(changeListReady(int, const QList<ChangeItem> &)),
                 this, SLOT(unsureBuildChanges(int, const QList<ChangeItem> &)));
    }

    chin->fetchData(buildNumber+1);
    m_buildCommitsApi.insert(buildNumber+1, chin);

    BuildStatus * bs = m_buildStatusApi.value(buildNumber);
    Q_ASSERT(bs);
    m_buildStatusApi.remove(buildNumber);
    delete bs;
}

