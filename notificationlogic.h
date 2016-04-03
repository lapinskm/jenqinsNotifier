#ifndef NOTIFICATIONLOGIC_H
#define NOTIFICATIONLOGIC_H

#include <QObject>

class NotificationRule;
class BuildStatus;

class NotificationLogic : public QObject
{
    Q_OBJECT
public:
    explicit NotificationLogic(QObject *parent = 0);
    void start();

private slots:
    void timerEvent(QTimerEvent *);
private:
    QList <NotificationRule *> m_rules;
    QList <BuildStatus *> m_jobsStatus;
};

#endif // NOTIFICATIONLOGIC_H
