#ifndef BUILDAPIHANDLER_H
#define BUILDAPIHANDLER_H

#include "xmlapihandler.h"

class BuildApiHandler : public XmlApiHandler
{
public:
    BuildApiHandler(QObject *parent = nullptr) : XmlApiHandler(parent), m_buildNumber (-1) {}
    QString url() const;

    void setJobName(const QString &jobName) { m_jobName = jobName; }
    void setBuildNumber(int buildNumber) { m_buildNumber = buildNumber; }

protected:
    QString m_jobName;
    int m_buildNumber;
};

#endif // BUILDAPIHANDLER_H
