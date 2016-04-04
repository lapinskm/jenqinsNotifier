#ifndef NOTIFICATIONRULEDATA_H
#define NOTIFICATIONRULEDATA_H

#include <QStringList>

#include "buildresult.h"

class QDomElement;
class QDomDocument;

class NotificationRuleData
{
public:
    NotificationRuleData(const QDomElement &ruleDataElement);
    NotificationRuleData();
    QDomElement toXml(QDomDocument &doc) const;
    void setSettingData(const QString & jobName, bool notifyFailures, bool filterByCommiter,
                        const QStringList & commiters, bool notifyEndOfFailSpree);

    QString jobName() { return m_jobName; }
    bool notifyFailures() { return m_notifyFailures; }
    bool filterByCommiter() { return m_filterByCommiter; }
    QStringList commiters() { return m_commiters; }
    bool notifyEndOfFailSpree () { return m_notifyEndOfFailSpree; }

private:
    QString m_jobName;
    bool m_notifyFailures;
    bool m_filterByCommiter;
    QStringList m_commiters;
    bool m_notifyEndOfFailSpree;
};

#endif // NOTIFICATIONRULEDATA_H
