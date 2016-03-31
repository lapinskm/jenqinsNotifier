#ifndef JOBLIST_H
#define JOBLIST_H

#include "xmlapihandler.h"

class JobList :public XmlApiHandler
{
    Q_OBJECT
public:
    JobList(const QString & host, QObject *parent = nullptr) : XmlApiHandler(host, parent) {}
    QList<QString> jobNames() const { return m_jobNames; }

signals:
    void jobListReady();

private:
    void processXml(const QDomDocument &);
    QString url() const;

    QList<QString> m_jobNames;
};

#endif // JOBLIST_H
