#include "buildchanges.h"

#include <QDomDocument>
#include <QDebug>

void ChangesInfo::processXml(const QDomDocument &xml)
{
    qDebug()<<Q_FUNC_INFO<<xml.toString();
}

QString ChangesInfo::url()
{
    QString ret= BuildApiHandler::url();
    ret.append("?tree=changeSet[*[*[*]]]");
    return ret;
}
