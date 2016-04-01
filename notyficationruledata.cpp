#include "notyficationruledata.h"

#include <QDomDocument>

notyficationRuleData::notyficationRuleData()
    : m_lastBuildNumber (-1)
    , m_lastResult (noStatus)
    , m_jobName ("")
    , m_notifyFailures(false)
    , m_filterByCommiter (false)
    , m_notifyEndOfFailSpree (false)
{}

notyficationRuleData::notyficationRuleData(const QDomElement & ruleDataElement)
{
    m_jobName = childTextByTagName(ruleDataElement, "job_name");
    m_notifyFailures = childTextByTagName(ruleDataElement,"notify_failures").contains("true");
    m_filterByCommiter = childTextByTagName(ruleDataElement,"filter_by_commiters").contains("true");
    QDomNodeList commitersNodes = ruleDataElement.elementsByTagName("commiters");
    for (int i =0; i<commitersNodes.size();++i ) {
        QDomNodeList commitersNodes = commitersNodes.at(i).toElement().elementsByTagName("commiter");
         for (int j =0; j<commitersNodes.size(); ++j ) {
             m_commiters.append(commitersNodes.at(i).toElement().text());
         }
    }
    m_lastBuildNumber = childTextByTagName(ruleDataElement,"last_build_number").toInt();
    m_lastResult = static_cast<BuildResult>(childTextByTagName(ruleDataElement,"last_buid_result").toInt());
}

QDomElement notyficationRuleData::toXml(QDomDocument &doc) const
{
    QDomElement ruleDataElement = doc.createElement("rule");

    appendTextElement(doc, ruleDataElement, "job_name", m_jobName);
    appendTextElement(doc, ruleDataElement, "notify_failures", m_notifyFailures ? "true" : "false");
    appendTextElement(doc, ruleDataElement, "filter_by_commiters", m_filterByCommiter ? "true" : "false");
    QDomElement commitersElement = doc.createElement("commiters");
    foreach (QString commiter, m_commiters) {
        appendTextElement(doc, commitersElement, "commiter", commiter);
    }
    ruleDataElement.appendChild(commitersElement);
    appendTextElement(doc, ruleDataElement, "last_build_number", QString::number(m_lastBuildNumber));
    appendTextElement(doc, ruleDataElement, "last_buid_result", QString::number(m_lastResult));

    return ruleDataElement;
}

void notyficationRuleData::setSettingData(const QString & jobName, bool notifyFailures, bool filterByCommiter,
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

void notyficationRuleData::appendTextElement(QDomDocument & doc, QDomElement & parent,
                                             const QString & tagname, const QString & text)
{
    QDomElement element = doc.createElement(tagname);
    element.appendChild(doc.createTextNode(text));
    parent.appendChild(element);
}

QString notyficationRuleData::childTextByTagName(const QDomElement & parent, const QString & tagname)
{
    QDomNodeList childNodes = parent.elementsByTagName(tagname);
    if (!childNodes.isEmpty()) {
       return childNodes.at(0).toElement().text();
    }
    return QString();
}

