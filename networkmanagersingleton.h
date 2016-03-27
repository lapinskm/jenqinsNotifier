#ifndef NETWORKMANAGERSINGLETON_H
#define NETWORKMANAGERSINGLETON_H

#include <QNetworkAccessManager>

class NetworkManagerSingleton: public QNetworkAccessManager
{
public:
    static NetworkManagerSingleton & instance();
    void operator = (const  NetworkManagerSingleton &) = delete;

private:
    NetworkManagerSingleton(){}
};

#endif // NETWORKMANAGERSINGLETON_H
