#include "uimanager.h"
#include "dataTypes/notificationdata.h"

#include <QDebug>
#include <QQuickView>
#include <QQuickItem>

UiManager::UiManager(QObject *parent)
    : QObject(parent)
    , m_view(new QQuickView(QUrl("ui/mainView.qml")))
{
    connect(m_view->rootObject(), SIGNAL(settingsButtonClicked()), this, SLOT(showSettings()));
    connect(m_view->rootObject(), SIGNAL(stopButtonClicked()), this, SLOT(closeButtonClicked()));
}

UiManager::~UiManager()
{
    m_view->deleteLater();
}

void UiManager::showNotification(const NotyficationData &)
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: impelment this.
}

void UiManager::showMainView()
{
    qDebug()<<Q_FUNC_INFO;
    m_view->show();
}

void UiManager::showSettings()
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: impelment this.
}

void UiManager::closeButtonClicked()
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: Show confirmaton popup.
    emit userWantToClose();
}

