#ifndef SINGLEINSTANCEGUARD_H
#define SINGLEINSTANCEGUARD_H

#include <QObject>
#include <QLocalSocket>

class QLockFile;
class QLocalServer;

class SingleInstanceGuard : public QObject
{
    Q_OBJECT

public:
    SingleInstanceGuard(QObject * parent = nullptr);
    ~SingleInstanceGuard();
    void tryStart();


signals:
    void anotherInstanceTriedToStart();
    void anotherInstanceAlreadyExist();
    void thisInstanceIsFirst();
    void errorOccured();

private slots:
    void connectedToServer();
    void connectionFailed(QLocalSocket::LocalSocketError);
    void sockedConnected();

private:
    void clearLock();

    QString m_identyficationString;
    QLockFile *m_lock;
    QLocalServer *m_server;
    QLocalSocket *m_socket;
};

#endif // SINGLEINSTANCEGUARD_H
