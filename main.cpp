#include <QCoreApplication>
#include "poller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Poller p;
    p.start();
    return a.exec();
}
