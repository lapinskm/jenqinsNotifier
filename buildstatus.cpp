#include "buildstatus.h"

#include <QDebug>
#include <QDomDocument>
#include <QUrl>

QMap<QString, BuildStatus::buildResult> BuildStatus::m_stringToResultMap = QMap<QString, BuildStatus::buildResult>();
BuildStatus::BuildStatus(QObject *parent)
    : XmlApiHandler(parent)
    , m_buildNumber (-1)
{
    if(m_stringToResultMap.empty()) {
        m_stringToResultMap.insert("SUCCESS", success);
        m_stringToResultMap.insert("FAILURE", failure);
        m_stringToResultMap.insert("ABORTED", aborted);
        m_stringToResultMap.insert("UNSTABLE", unstable);
    }
}

void BuildStatus::processXml(const QDomDocument &xml)
{
    QDomNodeList results = xml.elementsByTagName("result");
    if (!results.isEmpty()) {
        m_result=m_stringToResultMap.value(results.at(0).toElement().text(), noStatus);
        qDebug()<<Q_FUNC_INFO<<results.at(0).toElement().text();
    }
    emit buildStatusReady(m_jobName);
}

QString BuildStatus::url() const
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
