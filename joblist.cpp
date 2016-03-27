#include "joblist.h"

#include <QDomDocument>
#include <QDebug>

void JobList::processXml(const QDomDocument & xml)
{
    m_jobNames.clear();
    QDomNodeList jobNodes = xml.elementsByTagName("job");
    for (int i = 0; i < jobNodes.size(); i++) {
            QDomNodeList nameNodes = jobNodes.at(i).toElement().elementsByTagName("name");
            QDomNodeList colorNodes = jobNodes.at(i).toElement().elementsByTagName("color");
            if (!nameNodes.isEmpty() && !colorNodes.isEmpty())
            {
                QString color = colorNodes.at(0).toElement().text();
                //ignore jobs without builds.
                if( color == "disabled" ||
                    color == "notbuilt")
                    continue;

                m_jobNames.append(nameNodes.at(0).toElement().text());
                qDebug()<<Q_FUNC_INFO<<m_jobNames.last();
            }
    }
    emit jobListReady();
}

QString JobList::url() const
{
    QString url = host();
    return url.append("/api/xml?tree=jobs[name,color]&wrapper=jobs");

}


