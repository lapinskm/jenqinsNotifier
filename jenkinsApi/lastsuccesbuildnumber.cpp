#include "lastsuccesbuildnumber.h"

#include <QDebug>

void LastSuccesBuildNumber::processReply(const QString & reply)
{
    bool ok;
    int number = reply.toInt(&ok);
    if (!ok) {
        qWarning()<<Q_FUNC_INFO<<"No number in reply!!! Reply: "<<reply;
        number = -1;
    }
    emit buildNumberReady(m_jobName, number);
}

QString LastSuccesBuildNumber::url()
{
    QString ret = host();
    if (!ret.endsWith("/"))
        ret.append("/");
    ret.append(m_jobName);
    return ret.append("/lastStableBuild/buildNumber");
}
