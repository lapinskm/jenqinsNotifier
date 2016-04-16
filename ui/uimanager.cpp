#include "uimanager.h"
#include "dataTypes/notificationdata.h"

#include <QDebug>
#include <QQuickView>

UiManager::UiManager(QObject *parent)
    : QObject(parent)
    , m_settings(new QQuickView(QUrl("ui/settings.qml")))
{
}

UiManager::~UiManager()
{
    m_settings->deleteLater();
}



void UiManager::showNotification(const NotyficationData &)
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: impelment this.
}

void UiManager::showSettings()
{
    qDebug()<<Q_FUNC_INFO;

    m_settings->show();
    //TODO: impelment this.
}

