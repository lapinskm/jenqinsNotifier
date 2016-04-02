#ifndef XMLUTILS_H
#define XMLUTILS_H

class QDomDocument;
class QDomElement;
class QString;

class XmlUtils
{
public:
    static void appendTextElement(QDomDocument & doc, QDomElement & parent,
                                  const QString & tagname, const QString & text);
    static QString elementTextByPath(const QDomElement & parent, const QString & tagname);

private:
    XmlUtils(){}
};

#endif // XMLUTILS_H
