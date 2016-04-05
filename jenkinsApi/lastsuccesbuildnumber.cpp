#include "lastsuccesbuildnumber.h"

#include <QDebug>

void LastSuccesBuildNumber::processReply(const QString & reply)
{
    bool ok;
    int number = reply.toInt(&ok);
    if (!ok) {
        qWarning()<<Q_FUNC_INFO<<"No number in reply!!! URL: "<<url()<<" Reply: "<<reply;
        number = -1;
    }
    emit buildNumberReady(number);
}

QString LastSuccesBuildNumber::url() const
{
    QString ret = host();
    if (!ret.endsWith("/"))
        ret.append("/");
    ret.append("job/");
    ret.append(m_jobName);
    return ret.append("/lastStableBuild/buildNumber");
}
