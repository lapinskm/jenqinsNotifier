#ifndef JOBLIST_H
#define JOBLIST_H

#include "xmlapihandler.h"

class JobList :public XmlApiHandler
{
    Q_OBJECT
public:
    JobList(QObject *parent = nullptr) : XmlApiHandler(parent) {}
    QList<QString> jobNames() const { return m_jobNames; }

signals:
    void jobListReady();

private:
    void processXml(const QDomDocument &);
    QString url() const;

    QList<QString> m_jobNames;
};

#endif // JOBLIST_H
