#ifndef LASTSUCCESBUILDNUMBER_H
#define LASTSUCCESBUILDNUMBER_H

#include "apihandler.h"

class LastSuccesBuildNumber : public ApiHandler
{
    Q_OBJECT
public:
    LastSuccesBuildNumber(QObject * parent = nullptr) : ApiHandler(parent) {}
    void setJobName(const QString &jobName) { m_jobName = jobName; }

signals:
    void buildNumberReady(QString JobName, int number);

private:
    void processReply(const QString &);
    QString url();

    QString m_jobName;
};

#endif // LASTSUCCESBUILDNUMBER_H
