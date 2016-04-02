#include "xmlutils.h"

#include <QDomDocument>
#include <QStringList>

void XmlUtils::appendTextElement(QDomDocument & doc, QDomElement & parent,
                                 const QString & tagname, const QString & text)
{
    QDomElement element = doc.createElement(tagname);
    element.appendChild(doc.createTextNode(text));
    parent.appendChild(element);
}

QString XmlUtils::elementTextByPath(const QDomElement & parent, const QString & path)
{
    QDomElement currentElement = parent;
    foreach (QString tagName, path.split("/")) {
        QDomNodeList childNodes = currentElement.elementsByTagName(tagName);
        if (!childNodes.isEmpty()) {
           currentElement = childNodes.at(0).toElement();
        }
        else {
            return QString();
        }
    }
    return currentElement.text();
}
