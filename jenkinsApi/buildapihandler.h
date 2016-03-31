#ifndef BUILDAPIHANDLER_H
#define BUILDAPIHANDLER_H

#include "xmlapihandler.h"

class BuildApiHandler : public XmlApiHandler
{
public:
    BuildApiHandler(const QString & host, const QString & jobName, int buildNumber = -1,  QObject *parent = nullptr)
        : XmlApiHandler(host, parent), m_jobName(jobName), m_buildNumber (buildNumber) {}
    QString url() const;

    void setBuildNumber(int buildNumber) { m_buildNumber = buildNumber; }

protected:
    QString m_jobName;
    int m_buildNumber;
};

#endif // BUILDAPIHANDLER_H
