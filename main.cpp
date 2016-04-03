#include <QCoreApplication>
#include "notificationlogic.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NotificationLogic logic;
    logic.start();
    return a.exec();
}
