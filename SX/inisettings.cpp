#include "inisettings.h"

IniSettings IniSettings::instance;

IniSettings::IniSettings(QObject *parent) : QObject(parent)
{

}

IniSettings &IniSettings::GetInstance()
{
    return instance;
}

void IniSettings::settings_init(const QString &path)
{
    /*QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += path;*/
    m_iniFile = QSharedPointer<QSettings>(new QSettings(path, QSettings::IniFormat));
    /*QFile file(path);
    if (false == file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_iniFile->beginGroup("section");
        m_iniFile->setValue("status", "false");
        m_iniFile->endGroup();
    }*/
}

void IniSettings::setValue(const QString &section, const QString &key, const QString &value)
{
    m_iniFile->setIniCodec(QTextCodec::codecForName("System")); //确保中文能使用
    m_iniFile->beginGroup(section);     // 设置节点名
    m_iniFile->setValue(key, value);    //设置键名和键值
    m_iniFile->endGroup();              // 结束当前节的操作
}

void IniSettings::removeNode(const QString &section)
{
    m_iniFile->setIniCodec(QTextCodec::codecForName("System")); //确保中文能使用
    m_iniFile->remove(section);
}

void IniSettings::removeKey(const QString &section, const QString &key)
{
    m_iniFile->setIniCodec(QTextCodec::codecForName("System")); //确保中文能使用
    /*QString path = QString("%1/%2").arg(section).arg(key);
    m_iniFile->remove(path);*/
    m_iniFile->beginGroup(section);
    m_iniFile->remove(key);
    m_iniFile->endGroup();
}

//QString IniSettings::getValue(const QString &section, const QString &key)
QString IniSettings::getValue(const QString &section_Key)
{
    m_iniFile->setIniCodec(QTextCodec::codecForName("System")); //确保中文能使用

    //QString path = QString("%1/%2").arg(section).arg(key);

    //QString result = m_iniFile->value(path).toString();
    QString result = m_iniFile->value(section_Key).toString();
    return result;
}

QString IniSettings::getStrImp(QString skey, QString value)
{
    if (value == 0)
    {
        return getValue(skey);
    }
    else
    {
        QStringList _lst = skey.split("/");
        setValue(_lst.at(0),_lst.at(1),value);
        return value;
    }
}


QString IniSettings::self_AppPath()
{
    QString sPath = QCoreApplication::applicationDirPath() + "/";

    return sPath;
}
