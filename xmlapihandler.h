#ifndef XMLAPIHANDLER_H
#define XMLAPIHANDLER_H

#include <QObject>

class QNetworkReply;
class QDomDocument;

class XmlApiHandler: public QObject
{
    Q_OBJECT
public:
    XmlApiHandler(QObject * parent = nullptr)
        : QObject(parent), m_reply(nullptr) {}
    void setHost(QString const &host) { m_host = host; }
    QString host() const { return m_host; }
    void fetchData();

protected:
    virtual QString url() const = 0;
    virtual void processXml(const QDomDocument&) = 0;

private slots:
    void requestFinished();

private:
    QString m_host;
    QNetworkReply * m_reply;
    QString m_prevRedirect;
};

#endif // XMLAPIHANDLER_H
