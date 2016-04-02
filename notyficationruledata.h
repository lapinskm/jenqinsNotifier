#ifndef NOTYFICATIONRULEDATA_H
#define NOTYFICATIONRULEDATA_H

#include <QStringList>

#include "buildresult.h"

class QDomElement;
class QDomDocument;

class NotyficationRuleData
{
public:
    NotyficationRuleData(const QDomElement &ruleDataElement);
    NotyficationRuleData();
    QDomElement toXml(QDomDocument &doc) const;
    void setSettingData(const QString & jobName, bool notifyFailures, bool filterByCommiter,
                        const QStringList & commiters, bool notifyEndOfFailSpree);

private:
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
