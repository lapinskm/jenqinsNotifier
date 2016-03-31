#ifndef LASTSUCCESBUILDNUMBER_H
#define LASTSUCCESBUILDNUMBER_H

#include "apihandler.h"

class LastSuccesBuildNumber : public ApiHandler
{
    Q_OBJECT
public:
    LastSuccesBuildNumber(const QString & host, const QString & jobName, QObject * parent = nullptr)
        : ApiHandler(host, parent), m_jobName(jobName) {}

signals:
    void buildNumberReady(int number);

private:
    void processReply(const QString &);
    QString url() const;

    QString m_jobName;
};

#endif // LASTSUCCESBUILDNUMBER_H
