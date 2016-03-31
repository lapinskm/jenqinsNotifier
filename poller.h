#ifndef POLLER_H
#define POLLER_H

#include "buildresult.h"

#include <QObject>
#include <QHash>
#include <QStringList>

class JobList;
class BuildStatus;

class Poller : public QObject
{
    Q_OBJECT
public:
    explicit Poller(QObject *parent = 0);
    void setInterval(int interval){m_interval = interval;}
    void setHost(QString host);
    void start();

signals:
    void newBuildStatusInformation(const QString &jobName, int buildNumber, BuildResult result);

private slots:
    void jobStatusReady(const QString &jobName, int buildNumber);

private:
    void timerEvent(QTimerEvent *);

    QString m_host;
    int m_interval;
    QStringList m_watchedJobList;
    QHash <QString, BuildStatus*> m_jobsStatus;
};

#endif // POLLER_H
