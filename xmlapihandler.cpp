#include "xmlapihandler.h"
#include "networkmanagersingleton.h"

#include <QNetworkReply>
#include <QDomDocument>

void XmlApiHandler::fetchData()
{
    if (!m_reply) {
        m_reply = NetworkManagerSingleton::instance().get(QNetworkRequest(url()));
        connect(m_reply, SIGNAL(finished()), this, SLOT(requestFinished()));
    }
}

void XmlApiHandler::requestFinished()
{
    Q_ASSERT(m_reply);
    QByteArray responseString = m_reply->readAll();
    QDomDocument xml;
    if (xml.setContent(responseString))
        processXml(xml);
    else
       qWarning()<<"No xml in response!\nurl:"<<url()<<"\nResponse:\n"<<responseString;

    delete m_reply;
    m_reply=nullptr;
}
