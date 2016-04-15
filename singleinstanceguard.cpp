#include "singleinstanceguard.h"

#include <QLockFile>
#include <QLocalServer>

#include <QDebug>


SingleInstanceGuard::SingleInstanceGuard(QObject *parent)
    : QObject(parent)
    , m_identyficationString (QString::fromUtf8("jenqinsNotifier"))
    , m_lock(new QLockFile(m_identyficationString))
    , m_server(new QLocalServer(this))
    , m_socket(nullptr)
{
    connect(m_server, SIGNAL(newConnection()), this, SLOT(sockedConnected()));
}

SingleInstanceGuard::~SingleInstanceGuard()
{
    clearLock();
}

void SingleInstanceGuard::tryStart()
{
    qDebug()<< Q_FUNC_INFO;
    Q_ASSERT(m_lock);
    m_lock->removeStaleLockFile();
    if (m_lock->lock()) {
        Q_ASSERT(nullptr == m_socket);
        m_socket = new QLocalSocket();
        connect (m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
        connect (m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(connectionFailed(QLocalSocket::LocalSocketError)));
        m_socket->connectToServer(m_identyficationString);
    }
    else {
        qCritical() << Q_FUNC_INFO << "Cannot lock the lock file!!!" << "(\"" << m_identyficationString << "\")";
        emit errorOccured();
        clearLock();
    }

}

void SingleInstanceGuard::connectedToServer()
{
    qDebug()<<Q_FUNC_INFO<<"Another instance is running. Inform it about curently started.";
    Q_ASSERT(m_socket);
    m_socket->disconnectFromServer();
    m_socket->deleteLater();
    m_socket = nullptr;
    emit anotherInstanceAlreadyExist();
    clearLock();
}

void SingleInstanceGuard::connectionFailed(QLocalSocket::LocalSocketError err)
{
    Q_ASSERT(m_socket);
    if(QLocalSocket::ServerNotFoundError == err) {
        qDebug()<<Q_FUNC_INFO<<"No more instances are running.";
        emit thisInstanceIsFirst();
        m_server->listen(m_identyficationString);
    }
    else {
        qWarning()<< Q_FUNC_INFO<<"Unable to connect. Possibly previous instance crashed. Trying to start server.";
        if (!QLocalServer::removeServer(m_identyficationString))
            emit errorOccured();
        else if (!m_server->listen(m_identyficationString))
            qDebug()<<Q_FUNC_INFO<<err;
            emit errorOccured();
        else
            emit thisInstanceIsFirst();
    }
    clearLock();
}

void SingleInstanceGuard::sockedConnected()
{
     qDebug()<<Q_FUNC_INFO<<"Another instance tried to start.";
     emit anotherInstanceTriedToStart();
}

void SingleInstanceGuard::clearLock()
{
    if(m_lock) {
        m_lock->unlock();
        delete m_lock;
        m_lock = nullptr;
    }
}



