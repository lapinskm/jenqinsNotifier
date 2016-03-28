#include "settingssingleton.h"

#include <QCoreApplication>
#include <QDebug>

SettingsSingleton::SettingsSingleton()
{
    QString iniPath = QCoreApplication::applicationFilePath();
#ifdef WIN32
    iniPath.replace(".exe", "");
#endif
    iniPath.append(".ini");
    m_impl = new QSettings(iniPath, QSettings::IniFormat);
}

SettingsSingleton::~SettingsSingleton()
{
    delete m_impl;
}

SettingsSingleton &SettingsSingleton::instance()
{
    static SettingsSingleton inst;
    return inst;
}

QString SettingsSingleton::jenkinsUrl()
{
    return m_impl->value("jenkins_url", "https://127.0.0.1").toString();
}

void SettingsSingleton::setJenkinsUrl(QString url)
{
    m_impl->setValue("jenkins_url", url);
}

QStringList SettingsSingleton::watchedJobs()
{
    qDebug()<<m_impl->value("watched_jobs");
    return  m_impl->value("watched_jobs").toStringList();
}

void SettingsSingleton::setWatchedJobs(QStringList jobs)
{
     m_impl->setValue("watched_jobs", jobs);
}

int SettingsSingleton::pollInterval()
{
    return  m_impl->value("poll_interval").toInt();
}

void SettingsSingleton::setPollInterval(int interval)
{
     m_impl->setValue("poll_interval", interval);
}
