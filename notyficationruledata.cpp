#include "notyficationruledata.h"
#include "xmlutils.h"

#include <QDomDocument>

NotyficationRuleData::NotyficationRuleData()
    : m_lastBuildNumber (-1)
    , m_lastResult (noStatus)
    , m_jobName ("")
    , m_notifyFailures(false)
    , m_filterByCommiter (false)
    , m_notifyEndOfFailSpree (false)
{}

NotyficationRuleData::NotyficationRuleData(const QDomElement & ruleDataElement)
{
    m_jobName = XmlUtils::elementTextByPath(ruleDataElement, "job_name");
    m_notifyFailures = XmlUtils::elementTextByPath(ruleDataElement,"notify_failures").contains("true");
    m_filterByCommiter = XmlUtils::elementTextByPath(ruleDataElement,"filter_by_commiters").contains("true");
    QDomNodeList commitersNodes = ruleDataElement.elementsByTagName("committers");
    for (int i =0; i<commitersNodes.size();++i ) {
        QDomNodeList commiterNodes = commitersNodes.at(i).toElement().elementsByTagName("committer");
         for (int j =0; j<commiterNodes.size(); ++j ) {
             m_commiters.append(commiterNodes.at(j).toElement().text());
         }
    }
    m_lastBuildNumber = XmlUtils::elementTextByPath(ruleDataElement,"last_build_number").toInt();
    m_lastResult = static_cast<BuildResult>(XmlUtils::elementTextByPath(ruleDataElement,"last_buid_result").toInt());
    m_notifyEndOfFailSpree = XmlUtils::elementTextByPath(ruleDataElement,"notify_end_of_fail_spree").contains("true");
}

QDomElement NotyficationRuleData::toXml(QDomDocument &doc) const
{
    QDomElement ruleDataElement = doc.createElement("rule");

    XmlUtils::appendTextElement(doc, ruleDataElement, "job_name", m_jobName);
    XmlUtils::appendTextElement(doc, ruleDataElement, "notify_failures", m_notifyFailures ? "true" : "false");
    XmlUtils::appendTextElement(doc, ruleDataElement, "filter_by_commiters", m_filterByCommiter ? "true" : "false");
    QDomElement commitersElement = doc.createElement("committers");
    foreach (QString commiter, m_commiters) {
        XmlUtils::appendTextElement(doc, commitersElement, "committer", commiter);
    }
    ruleDataElement.appendChild(commitersElement);
    XmlUtils::appendTextElement(doc, ruleDataElement, "last_build_number", QString::number(m_lastBuildNumber));
    XmlUtils::appendTextElement(doc, ruleDataElement, "last_buid_result", QString::number(m_lastResult));
    XmlUtils::appendTextElement(doc, ruleDataElement, "notify_end_of_fail_spree", m_notifyEndOfFailSpree ? "true" : "false");
    return ruleDataElement;
}

void NotyficationRuleData::setSettingData(const QString & jobName, bool notifyFailures, bool filterByCommiter,
                                          const QStringList & commiters, bool notifyEndOfFailSpree)
{
    if(jobName != m_jobName) {
        m_lastBuildNumber = -1;
        m_lastResult = noStatus;
    }
    m_jobName = jobName;
    m_notifyFailures = notifyFailures;
    m_filterByCommiter = filterByCommiter;
    m_commiters = commiters;
    m_notifyEndOfFailSpree = notifyEndOfFailSpree;
}
