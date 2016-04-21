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
    void showMainView();
private slots:
    void showSettings();
    void closeButtonClicked();

private:
    QQuickView * m_view;

};

#endif // UIMANAGER_H
