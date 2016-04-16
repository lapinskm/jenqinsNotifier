#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>

class NotyficationData;

class UiManager : public QObject
{
    Q_OBJECT
public:
    explicit UiManager(QObject *parent = 0);
signals:
    void userWantToClose();

public slots:
    void showNotification(const NotyficationData &);
    void showSettings();

};

#endif // UIMANAGER_H
