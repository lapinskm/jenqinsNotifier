#ifndef CHANGESINFO_H
#define CHANGESINFO_H

#include "buildapihandler.h"
#include "dataTypes/changeitem.h"

#include <QString>
#include <QList>

class ChangesInfo : public BuildApiHandler
{
    Q_OBJECT
public:
    ChangesInfo(const QString & host,const QString & jobName, int buildNumber = -1, QObject *parent = nullptr)
        : BuildApiHandler(host, jobName, buildNumber, parent) {}
    void fetchData(int buildNumber);
signals:
    void changeListReady(int buildNumber, QList<ChangeItem>);

private:
    void processXml(const QDomDocument &xml);
    QString url() const;
};

#endif // CHANGESINFO_H
