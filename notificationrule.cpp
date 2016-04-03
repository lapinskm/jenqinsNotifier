#include "notificationrule.h"

#include <QDebug>

NotificationRule::NotificationRule(const NotificationRuleData & nrd, QObject *parent)
    : QObject(parent)
    ,  m_data (nrd)
{}

void NotificationRule::jobStatusReady(int buildNumber, const BuildResult & res)
{
    //TODO:implement this
    qDebug()<<Q_FUNC_INFO<<m_data.jobName()<<"/"<<buildNumber<<"/"<<res;
}
