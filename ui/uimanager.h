#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>

class NotyficationData;
class QQuickView;

class UiManager : public QObject
{
    Q_OBJECT
public:
    explicit UiManager(QObject *parent = 0);
    ~UiManager();
signals:
    void userWantToClose();

public slots:
    void showNotification(const NotyficationData &);
    void showSettings();

private:
    QQuickView * m_settings;

};

#endif // UIMANAGER_H
