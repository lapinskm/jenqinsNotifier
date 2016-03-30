#ifndef BUILDCHANGES_H
#define BUILDCHANGES_H

#include "buildapihandler.h"

class ChangesInfo : public BuildApiHandler
{
    Q_OBJECT
public:
    ChangesInfo(QObject *parent = nullptr) : BuildApiHandler(parent) {}

private:
    void processXml(const QDomDocument &xml);
    QString url();
};

#endif // BUILDCHANGES_H
