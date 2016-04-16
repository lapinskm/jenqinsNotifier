#include "uimanager.h"
#include "dataTypes/notificationdata.h"

#include <QDebug>

UiManager::UiManager(QObject *parent)
    : QObject(parent)
{}

void UiManager::showNotification(const NotyficationData &)
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: impelment this.
}

void UiManager::showSettings()
{
    qDebug()<<Q_FUNC_INFO;
    //TODO: impelment this.
}

