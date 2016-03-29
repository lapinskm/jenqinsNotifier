#include "xmlapihandler.h"

#include <QDomDocument>
#include <QDebug>

void XmlApiHandler::processReply(const QString & replyString)
{
    QDomDocument xml;
    if (xml.setContent(replyString))
        processXml(xml);
    else
       qWarning()<<Q_FUNC_INFO<<"No xml in response!\nurl:"<<url()<<"\nResponse:\n"<<replyString;
}
