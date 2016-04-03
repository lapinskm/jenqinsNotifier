#include "settingssingleton.h"

#include "xmlutils.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QStandardPaths>

const QString SettingsSingleton::m_dataFileName = "jenqinsNotifierData.xml";

SettingsSingleton::SettingsSingleton()
    : m_jenkinsUrl ("https://127.0.0.1:8080")
    , m_interval (10000)
{
    m_dataFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
#ifdef WIN32
    if (!m_dataFilePath.endsWith("\\"))
        m_dataFilePath.append("\\");
#else
    if (!m_dataFilePath.endsWith("/"))
       m_dataFilePath.append("/");
#endif
    QFile dataFile(m_dataFilePath.append(m_dataFileName));
    if  (!dataFile.open(QFile::ReadOnly) ) {
        qCritical()<<Q_FUNC_INFO<<"cannot open file: "<<m_dataFilePath;
    }
    else {
        parseXml(dataFile.readAll());
    }
    dataFile.close();
}

SettingsSingleton::~SettingsSingleton()
{
    //TODO: Save data to file.
}

SettingsSingleton &SettingsSingleton::instance()
{
    static SettingsSingleton inst;
    return inst;
}

void SettingsSingleton::parseXml(const QByteArray & xml)
{
    QDomDocument doc;
    if (!doc.setContent(xml)) {
        qCritical()<<Q_FUNC_INFO<<"File is not a xml document!!!";
        return;
    }
    QDomElement root = doc.documentElement();
    m_interval = XmlUtils::elementTextByPath(root,"interval").toInt();
    m_jenkinsUrl = XmlUtils::elementTextByPath(root,"jenqins_url");
    QDomNodeList rulesNodes = root.elementsByTagName("notyfication_rules");
    m_rulesData.clear();
    if(!rulesNodes.isEmpty())
    {
        QDomElement rulesElement = rulesNodes.at(0).toElement();
        QDomNodeList ruleNodes = rulesElement.elementsByTagName("rule");
        for(int i = 0; i< ruleNodes.size(); ++i ) {
            NotificationRuleData ruleData(ruleNodes.at(i).toElement());
            m_rulesData.insert(ruleData.jobName(),ruleData);
        }
    }
}
