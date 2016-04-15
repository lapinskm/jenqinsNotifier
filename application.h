#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class SingleInstanceGuard;
class NotificationLogic;

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int & argc, char *argv[]);

signals:

private slots:
    void onThisInstanceIsFirst();
    void onAnotherInstanceAlreadyExist();

private:
    SingleInstanceGuard * m_singleInstanceGuard;
    NotificationLogic * m_notificationLogic;
};

#endif // APPLICATION_H
