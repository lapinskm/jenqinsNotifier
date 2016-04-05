#ifndef NOTIFICATIONDATA_H
#define NOTIFICATIONDATA_H

#include "changeitem.h"
#include "buildresult.h"

#include <QList>
#include <QString>

struct NotyficationData {
    int m_buildNumber;
    QString m_jobName;
    QString m_jenkinsHost;
    QList <ChangeItem> m_suspectedChanges;
    BuildResult m_result;
};

#endif // NOTIFICATIONDATA_H
