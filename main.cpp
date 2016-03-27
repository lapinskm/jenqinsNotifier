#include <QCoreApplication>
#include "poller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Poller p;
    p.setHost("https://builds.apache.org");
    p.start();
    return a.exec();
}
