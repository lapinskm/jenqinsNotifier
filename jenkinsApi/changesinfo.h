#ifndef CHANGESINFO_H
#define CHANGESINFO_H

#include "buildapihandler.h"
#include <QString>
#include <QList>

struct ChangeItem
{
    QString m_author;
    QString m_revision;
    QString m_repo;
};

class ChangesInfo : public BuildApiHandler
{
    Q_OBJECT
public:
    ChangesInfo(const QString & host,const QString & jobName, int buildNumber = -1, QObject *parent = nullptr)
        : BuildApiHandler(host, jobName, buildNumber, parent) {}
signals:
    void changeListReady(QList<ChangeItem>);

private:
    void processXml(const QDomDocument &xml);
    QString url();
};

#endif // CHANGESINFO_H
