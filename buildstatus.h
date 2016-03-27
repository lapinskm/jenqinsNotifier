#ifndef BUILDSTATUS_H
#define BUILDSTATUS_H

#include <xmlapihandler.h>
#include <QMap>

class BuildStatus : public XmlApiHandler
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
    void setJobName(QString jobName) { m_jobName = jobName; }
    void setBuildNumber(int buildNumber = -1) { m_buildNumber = buildNumber; }
    int buildNumber() const { return m_buildNumber; }

signals:
    void buildStatusReady(const QString &);

private:
    void processXml(const QDomDocument &xml);
    QString url() const;

    QString m_jobName;
    buildResult m_result;
    static QMap<QString, buildResult> m_stringToResultMap;
    int m_buildNumber;
};

#endif // BUILDSTATUS_H
