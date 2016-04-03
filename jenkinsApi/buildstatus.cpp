#include "buildstatus.h"
#include "xmlutils.h"

#include <QDebug>
#include <QDomDocument>

QMap <QString, BuildResult> BuildStatus::m_stringToResultMap = QMap<QString, BuildResult>();

BuildStatus::BuildStatus(const QString &host, const QString &jobName, int buildNumber, QObject *parent)
    : BuildApiHandler(host,jobName, buildNumber, parent)
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
    int buildNumber = XmlUtils::elementTextByPath(xml.documentElement(),"number").toInt();
    BuildResult result  = m_stringToResultMap.value(XmlUtils::elementTextByPath(xml.documentElement(), "result"), noStatus);
    emit buildStatusReady(buildNumber, result);
}
