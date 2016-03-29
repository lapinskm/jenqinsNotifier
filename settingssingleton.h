#ifndef SETTINGSSINGLETON_H
#define SETTINGSSINGLETON_H

#include <QSettings>

class SettingsSingleton
{
private:
    SettingsSingleton();
public:
     ~SettingsSingleton();

    QString jenkinsUrl();
    void setJenkinsUrl(QString);
    QStringList watchedJobs();
    void setWatchedJobs(QStringList);
    int pollInterval();
    void setPollInterval(int interval);

    static SettingsSingleton & instance();
    void operator = (const  SettingsSingleton &) = delete;

private:
    QSettings* m_impl;
};

#endif // SETTINGSSINGLETON_H
