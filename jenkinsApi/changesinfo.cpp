#include "changesinfo.h"
#include "xmlutils.h"

#include <QDomDocument>
#include <QDebug>

void ChangesInfo::fetchData(int buildNumber)
{
    setBuildNumber(buildNumber);
    BuildApiHandler::fetchData();
}

void ChangesInfo::processXml(const QDomDocument &xml)
{
    QList<ChangeItem> changes;
    QDomNodeList changeSetNodes = xml.elementsByTagName("changeSet");
    if(!changeSetNodes.isEmpty()) {
        QDomElement changeSetElement = changeSetNodes.at(0).toElement();
        QDomNodeList changeNodes = changeSetElement.elementsByTagName("item");
        for (int i = 0; i< changeNodes.size(); ++i) {
            ChangeItem item;
            item.m_author = XmlUtils::elementTextByPath(changeNodes.at(i).toElement(),"author/fullName");
            item.m_revision = XmlUtils::elementTextByPath(changeNodes.at(i).toElement(),"commitId");
            changes.append(item);
        }
    }
    emit changeListReady(buildNumber(), changes);
}

QString ChangesInfo::url() const
{
    QString ret= BuildApiHandler::url();
    ret.append("?tree=changeSet[*[*[*]]]");
    return ret;
}
