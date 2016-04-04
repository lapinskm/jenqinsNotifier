#ifndef BUILDSTATUS_H
#define BUILDSTATUS_H

#include "buildapihandler.h"
#include "dataTypes/buildresult.h"

#include <QMap>

class BuildStatus : public BuildApiHandler
{
    Q_OBJECT
public:
    BuildStatus(const QString & host, const QString & jobName, int buildNumber = -1, QObject * parent = nullptr);

signals:
    void buildStatusReady(int buildNumber, const BuildResult &);

private:
    void processXml(const QDomDocument &xml);

    static QMap<QString, BuildResult> m_stringToResultMap;
};

#endif // BUILDSTATUS_H
