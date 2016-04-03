#include "notificationlogic.h"
#include "notificationrule.h"
#include "jenkinsApi/buildstatus.h"
#include "settingssingleton.h"

#include <QDebug>

NotificationLogic::NotificationLogic(QObject *parent)
    : QObject(parent)
{
    foreach (NotificationRuleData nrd, SettingsSingleton::instance().ruleData()) {
        BuildStatus * stat = new BuildStatus(SettingsSingleton::instance().jenkinsUrl(), nrd.jobName(), -1, this);
        NotificationRule * rule = new NotificationRule(nrd, this);
        connect (stat, SIGNAL(buildStatusReady(int, const BuildResult &)),
                 rule, SLOT(jobStatusReady(int, const BuildResult & )));
        m_jobsStatus.append(stat);
        m_rules.append(rule);
    }
}

void NotificationLogic::start()
{
    int interval = SettingsSingleton::instance().pollInterval();
    qDebug() << Q_FUNC_INFO << "interval:" << interval;
    if( 0 < interval )
        startTimer(interval);
    else
        qWarning() << Q_FUNC_INFO << "Interval should be greater than 0 !!!";
}

void NotificationLogic::timerEvent(QTimerEvent *)
{
    foreach(BuildStatus * stat, m_jobsStatus) {
        stat->fetchData();
    }
}
