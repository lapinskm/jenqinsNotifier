#ifndef NOTYFICATIONRULEDATA_H
#define NOTYFICATIONRULEDATA_H

#include <QStringList>

#include "buildresult.h"

class QDomElement;
class QDomDocument;

class notyficationRuleData
{
public:
    notyficationRuleData(const QDomElement &ruleDataElement);
    notyficationRuleData();
    QDomElement toXml(QDomDocument &doc) const;
    void setSettingData(const QString & jobName, bool notifyFailures, bool filterByCommiter,
                        const QStringList & commiters, bool notifyEndOfFailSpree);

private:

    static void appendTextElement(QDomDocument & doc, QDomElement & parent,
                           const QString & tagname, const QString & text);
    static QString childTextByTagName(const QDomElement & parent, const QString & tagname);
    int m_lastBuildNumber;
    BuildResult m_lastResult;

    //setting data.
    QString m_jobName;
    bool m_notifyFailures;
    bool m_filterByCommiter;
    QStringList m_commiters;
    bool m_notifyEndOfFailSpree;
};

#endif // NOTYFICATIONRULEDATA_H
