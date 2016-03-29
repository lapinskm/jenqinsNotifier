#include "apihandler.h"
#include "networkmanagersingleton.h"

#include <QNetworkReply>

void ApiHandler::fetchData()
{
    if (!m_reply) {
        m_reply = NetworkManagerSingleton::instance().get(QNetworkRequest(url()));
        connect(m_reply, SIGNAL(finished()), this, SLOT(requestFinished()));
    }
}

void ApiHandler::requestFinished()
{
    Q_ASSERT(m_reply);
    QByteArray responseData = m_reply->readAll();
    processReply(QString (responseData));

    delete m_reply;
    m_reply = nullptr;
}

