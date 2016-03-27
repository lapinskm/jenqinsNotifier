#include "networkmanagersingleton.h"

NetworkManagerSingleton & NetworkManagerSingleton::instance()
{
    static NetworkManagerSingleton inst;
    return inst;
}
