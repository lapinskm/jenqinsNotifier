#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>

class QNetworkReply;

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    ApiHandler(QObject *parent = nullptr)
      : QObject(parent), m_reply(nullptr) {}
public:
    void setHost(QString const &host) { m_host = host; }
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
