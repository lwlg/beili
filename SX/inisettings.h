#ifndef INISETTINGS_H
#define INISETTINGS_H

#include <QObject>
#include <QSettings>
#include <QSharedPointer>
#include <QTextCodec>
#include <QCoreApplication>
#include <QFile>


#define theIni IniSettings::GetInstance()

class IniSettings : public QObject
{
    Q_OBJECT
public:
    explicit IniSettings(QObject *parent = 0);

    static IniSettings& GetInstance();
    static QString self_AppPath();

    void settings_init(const QString &path); //初始化QSettings对象，并读取ini配置文件,如果不存在配置文件，则创建

    void removeNode(const QString &section);                           //移除节点(包括其中所有的键值)
    void removeKey(const QString &section, const QString &key);        //移除节点中的某个键值

    ///
    QString getStrImp(QString skey,QString value=0);

protected:
    void setValue(const QString &section, const QString &key, const QString &value); //写入配置项（section:节点，key:键名，value:键值）
    QString getValue(const QString &section_Key);

signals:

public slots:

protected:
    static IniSettings instance;

public:
    QSharedPointer<QSettings> m_iniFile;
};

#endif // INISETTINGS_H
