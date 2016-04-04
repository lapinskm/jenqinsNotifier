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
    QList <ChangeItem> m_suspectedItems;
}

#endif // NOTIFICATIONDATA_H
