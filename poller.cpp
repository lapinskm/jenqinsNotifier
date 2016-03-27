#include "poller.h"
#include "joblist.h"
#include "buildstatus.h"

#include <QDebug>

Poller::Poller(QObject *parent)
    : QObject(parent)
    , m_jobList (new JobList(this))
{
    connect(m_jobList, SIGNAL( jobListReady() ), this, SLOT( jobListReady() ) );
}

void Poller::setHost(QString host)
{
    Q_ASSERT(m_jobList);
    m_host = host;
    m_jobList->setHost(host);
}

void Poller::start()
{
    qDebug()<<Q_FUNC_INFO;
    Q_ASSERT(m_jobList);
    m_jobList->fetchData();
}

void Poller::jobListReady()
{
    startTimer(m_interval);
    Q_ASSERT(m_jobList);

    foreach(QString jobName, m_jobList->jobNames())
    {
        BuildStatus * stat = new BuildStatus();
        stat->setHost(m_host);
        stat->setJobName(jobName);
        m_jobsStatus.insert(jobName, stat);
        stat->fetchData();
    }
}

void Poller::jobStatusReady(const QString & jobName)
{
    //todo:
}

void Poller::timerEvent(QTimerEvent *)
{
    foreach(BuildStatus *stat, m_jobsStatus)
    {
        connect(stat, SIGNAL(buildStatusReady(const QString &)), this, SLOT(jobStatusReady(const QString &)) );
        stat->fetchData();
    }
}
