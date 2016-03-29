#include "buildapihandler.h"

#include <QUrl>

QString BuildApiHandler::url() const
{
    QString ret = host();
    if (!ret.endsWith("/"))
        ret.append("/");
    ret.append("job/");
    ret.append(QUrl::toPercentEncoding(m_jobName));
    ret.append("/");
    ret.append(m_buildNumber==-1 ? "lastBuild" : QString::number(m_buildNumber));
    return ret.append("/api/xml");
}
