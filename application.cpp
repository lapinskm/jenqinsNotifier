#include "application.h"
#include "singleinstanceguard.h"
#include "notificationlogic.h"
#include "ui/uimanager.h"

#include <cstdlib>
#include <QDebug>

Application::Application(int & argc, char *argv[])
    : QApplication(argc, argv)
    , m_singleInstanceGuard(new SingleInstanceGuard(this))
    , m_notificationLogic(nullptr)
    , m_uiManager(nullptr)
{
    connect (m_singleInstanceGuard, SIGNAL(anotherInstanceAlreadyExist()),
             this, SLOT(onAnotherInstanceAlreadyExist()));
    connect (m_singleInstanceGuard, SIGNAL(thisInstanceIsFirst()),
             this, SLOT(onThisInstanceIsFirst()));
    m_singleInstanceGuard->tryStart();
}

void Application::onThisInstanceIsFirst()
{
    qDebug()<<Q_FUNC_INFO;
    Q_ASSERT(!m_notificationLogic && !m_uiManager);
    m_notificationLogic = new NotificationLogic(this);
    m_uiManager = new UiManager(this);
    connect(m_singleInstanceGuard, SIGNAL(anotherInstanceTriedToStart()),
            m_uiManager, SLOT(showSettings()));
    connect(m_uiManager, SIGNAL(userWantToClose()), this, SLOT(onUserWantToClose()));
    m_notificationLogic->start();
}

void Application::onAnotherInstanceAlreadyExist()
{
    qDebug()<<Q_FUNC_INFO<<"Another instance is already running. Closing...";
    std::exit(0);//using std::exit because cannot guarantee there is event loop running.
}

void Application::onUserWantToClose()
{
    quit();
}
