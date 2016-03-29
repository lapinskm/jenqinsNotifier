#ifndef BUILDSTATUS_H
#define BUILDSTATUS_H

#include "buildapihandler.h"

#include <QMap>

class BuildStatus : public BuildApiHandler
{
    Q_OBJECT
public:
    enum buildResult{
        noStatus = 0,
        success = 1,
        failure = 2,
        aborted = 3,
        unstable = 4,
        end
    };

    BuildStatus(QObject * parent = nullptr);

signals:
    void buildStatusReady(const QString &, int);

private:
    void processXml(const QDomDocument &xml);

    static QMap<QString, buildResult> m_stringToResultMap;

    int m_firstFailBuild;
    buildResult m_result;
};

#endif // BUILDSTATUS_H
