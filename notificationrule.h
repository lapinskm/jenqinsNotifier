#ifndef NOTIFICATIONRULE_H
#define NOTIFICATIONRULE_H

#include "dataTypes/notificationruledata.h"
#include "jenkinsApi/changesinfo.h"

#include <QHash>
#include <QObject>

class BuildStatus;
class ChangesInfo;
class LastSuccesBuildNumber;
class NotyficationData;


class NotificationRule : public QObject
{
    Q_OBJECT
public:
    explicit NotificationRule(const NotificationRuleData & nrd, QObject * parent = 0);
    ~NotificationRule();

public slots:
    void jobStatusReady(int buildNumber, const BuildResult & );
    void onLastSuccess(int buildNumber);
    void suspectedStatusReady(int buildNumber, const BuildResult &);
    void failingBuildChanges(int buildNumber, const QList<ChangeItem> &);
    void unsureBuildChanges(int buildNumber, const QList<ChangeItem> &);

signals:
    void notify(const NotyficationData &);

private:
    bool resultIsRevelant(BuildResult result) { return result == success || result == failure; }
    void checkNextBuild(int buildNumber);
    void notify();

    QString m_host;
    NotificationRuleData m_data;
    bool m_notifySuccess;
    bool m_isFailSpree;
    BuildResult m_lastRevelantResult;
    int m_lastBuildNumber;
    BuildResult m_lastResult;
    QHash<int, BuildStatus *> m_buildStatusApi;
    QHash<int, ChangesInfo *> m_buildCommitsApi;
    LastSuccesBuildNumber * m_lastSuccessApi;
    QList <ChangeItem> m_suspectedChanges;

    bool m_processing;
};

#endif // NOTIFICATIONRULE_H
