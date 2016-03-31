#ifndef XMLAPIHANDLER_H
#define XMLAPIHANDLER_H

#include "apihandler.h"

#include <QObject>

class QDomDocument;

class XmlApiHandler: public ApiHandler
{
    Q_OBJECT
public:
    XmlApiHandler(const QString & host, QObject * parent = nullptr)
        : ApiHandler(host, parent) {}
protected:
    virtual void processXml(const QDomDocument&) = 0;

private:
    void processReply(const QString &);
};

#endif // XMLAPIHANDLER_H
