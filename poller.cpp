#include "poller.h"
#include "joblist.h"
#include "buildstatus.h"
#include "settingssingleton.h"

#include <QDebug>
#include <QCoreApplication>

Poller::Poller(QObject *parent)
    : QObject( parent )
    , m_host ( SettingsSingleton::instance().jenkinsUrl() )
    , m_interval( SettingsSingleton::instance().pollInterval() )
    , m_watchedJobList( SettingsSingleton::instance().watchedJobs() )
{}

void Poller::start()
{
    qDebug()<<Q_FUNC_INFO;
    startTimer(m_interval);
}

void Poller::jobStatusReady(const QString & jobName)
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: Check state of job and notify if number of build has changed.
    if (m_jobsStatus.contains(jobName)) {
        delete m_jobsStatus.value(jobName);
        m_jobsStatus.remove(jobName);
    }
}

void Poller::timerEvent(QTimerEvent *)
{
    foreach(QString jobName, m_watchedJobList) {
        BuildStatus * stat = new BuildStatus();
        stat->setHost(m_host);
        stat->setJobName(jobName);
        m_jobsStatus.insert(jobName, stat);
        connect(stat, SIGNAL(buildStatusReady(const QString &)), this, SLOT(jobStatusReady(const QString &)) );
        stat->fetchData();
    }
}
