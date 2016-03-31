#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>

class QNetworkReply;

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    ApiHandler(const QString & host, QObject *parent = nullptr)
      : QObject(parent),m_host(host), m_reply(nullptr) {}
public:
    QString host() const { return m_host; }
    void fetchData();

protected:
    virtual QString url() const = 0;
    virtual void processReply(const QString &) = 0;

private slots:
    void requestFinished();

private:
    QString m_host;
    QNetworkReply * m_reply;
};

#endif // APIHANDLER_H
