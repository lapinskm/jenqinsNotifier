#ifndef SETTINGSSINGLETON_H
#define SETTINGSSINGLETON_H

#include "notyficationruledata.h"

#include <QHash>

class SettingsSingleton
{
private:
    SettingsSingleton();
public:
     ~SettingsSingleton();

    QString jenkinsUrl() { return m_jenkinsUrl; }
    void setJenkinsUrl(QString url) { m_jenkinsUrl = url; }
    QStringList watchedJobs() { return  m_rulesData.keys(); }
    void setRuleData(const QHash<QString, NotyficationRuleData> & ruleData)
    { m_rulesData = ruleData; }
    int pollInterval() { return m_interval; }
    void setPollInterval(int interval) {  m_interval = interval; }

    static SettingsSingleton & instance();
    void operator = (const  SettingsSingleton &) = delete;

private:
    void parseXml(const QByteArray &);

    QHash <QString, NotyficationRuleData> m_rulesData;
    QString m_jenkinsUrl;
    int m_interval;

    static const QString m_dataFileName;
    QString m_dataFilePath;
};

#endif // SETTINGSSINGLETON_H
