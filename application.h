#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class SingleInstanceGuard;
class NotificationLogic;
class UiManager;

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int & argc, char *argv[]);

signals:

private slots:
    void onThisInstanceIsFirst();
    void onAnotherInstanceAlreadyExist();
    void onUserWantToClose();

private:
    SingleInstanceGuard * m_singleInstanceGuard;
    NotificationLogic * m_notificationLogic;
    UiManager * m_uiManager;
};

#endif // APPLICATION_H
