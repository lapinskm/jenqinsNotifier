#include "buildstatus.h"

#include <QDebug>
#include <QDomDocument>

QMap <QString, BuildStatus::buildResult> BuildStatus::m_stringToResultMap = QMap<QString, BuildStatus::buildResult>();

BuildStatus::BuildStatus(QObject *parent)
    : BuildApiHandler(parent)
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
    QDomNodeList numbers = xml.elementsByTagName("number");
    if (!numbers.isEmpty()) {
        bool ok;
        int number = numbers.at(0).toElement().text().toInt(&ok);
        if (ok)
            m_buildNumber = number;
        qDebug()<<Q_FUNC_INFO<<numbers.at(0).toElement().text();
    }
    QDomNodeList results = xml.elementsByTagName("result");
    if (!results.isEmpty()) {
        m_result = m_stringToResultMap.value(results.at(0).toElement().text(), noStatus);
        qDebug()<<Q_FUNC_INFO<<results.at(0).toElement().text();
        emit buildStatusReady(m_jobName, m_buildNumber);
    }
    emit buildStatusReady(m_jobName, m_buildNumber);
}
