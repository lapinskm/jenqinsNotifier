#ifndef NOTIFICATIONRULE_H
#define NOTIFICATIONRULE_H

#include "dataTypes/notificationruledata.h"

#include <QObject>

class NotificationRule : public QObject
{
    Q_OBJECT
public:
    explicit NotificationRule(const NotificationRuleData & nrd, QObject * parent = 0);

public slots:
    void jobStatusReady(int buildNumber, const BuildResult & );

private:
    NotificationRuleData m_data;
};

#endif // NOTIFICATIONRULE_H
