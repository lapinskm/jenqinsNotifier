#ifndef POLLER_H
#define POLLER_H

#include <QObject>
#include <QHash>

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

private slots:
    void jobStatusReady(const QString &jobName);

private:
    void timerEvent(QTimerEvent *);

    QString m_host;
    int m_interval;
    QStringList m_watchedJobList;
    QHash <QString, BuildStatus*> m_jobsStatus;
};

#endif // POLLER_H
