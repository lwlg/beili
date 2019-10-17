#include "EasyLog.h"
#include <QDir>
#include <QDirIterator>
#include <QSettings>
#include <QApplication>
#include <QDebug>

EasyLog EasyLog::instance;


void EasyLog::InitLogHtml()
{
    QDir _applicationDir(QApplication::applicationDirPath());

    if (!_applicationDir.exists(_applicationDir.path() + "/log"))
    {
        _applicationDir.mkpath(_applicationDir.path() + "/log");
    }
    _applicationDir.cd("log");
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh-mm-ss");
    QString fileNamelog;
    fileNamelog+=date;
    fileNamelog+=" ";
    fileNamelog+=time;
    fileNamelog+=LOG_IDENTIFIER;
    QString _path = _applicationDir.path() + "/" + date;
    if (!_applicationDir.exists(_path))
    {
        _applicationDir.mkpath(_path);
    }
    _applicationDir.cd(date);

    m_index = 0;

    m_log.setFileName(_applicationDir.path() + "/" + fileNamelog);
    if (m_log.exists())m_log.remove();
    if (m_log.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Append))
    {
        m_stream.setDevice(&m_log);
        QString _logTitle =QString::fromUtf8("<html>\n<head>\n<title>日志记录</title>\n</head>\n<body>\n");
        m_stream << _logTitle;
    }
    else
    {
        QString _err = m_log.errorString();
    }
}

void EasyLog::InitLog()
{
    QDir _applicationDir(QApplication::applicationDirPath());

    if (!_applicationDir.exists(_applicationDir.path() + "/log"))
    {
        _applicationDir.mkpath(_applicationDir.path() + "/log");
    }
    _applicationDir.cd("log");


    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QDate delDate = QDate::currentDate().addDays(-7);

    qDebug()<<_applicationDir.path()+"/";
    DelLogFile(delDate,QDate::currentDate(),_applicationDir.path()+"/");

    //QString time = QTime::currentTime().toString("hh-mm-ss");
    QString fileNamelog;
    fileNamelog+=date;
    fileNamelog+=" ";
    //fileNamelog+=time;
    fileNamelog+=LOG_IDENTIFIER;

    //QString _path = _applicationDir.path() + "/" + date;
    //if (!_applicationDir.exists(_path))
    //{
    //    _applicationDir.mkpath(_path);
    //}
    //_applicationDir.cd(date);

    m_index = 0;

    m_log.setFileName(_applicationDir.path() + "/" + fileNamelog);
    //if (m_log.exists())m_log.remove(); //不写入同一文件
    if (m_log.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Append))
    {
        m_stream.setDevice(&m_log);
        QString _logTitle = QString::asprintf("//initial log success\n\n");
        m_stream << _logTitle;
    }
    else
    {
        QString _err = m_log.errorString();
    }
}

void EasyLog::DelLogFile(QDate begintime, QDate endtime, QString path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.log";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    if(dir.count() == 0)
    {
        return;
    }

    qDebug()<<"@@@@@";

    for (int var = 0; var < files.count(); var++)
    {
        QString fname = files[var];
        fname.left(10);
        qDebug()<<"@"<<fname;
        QDate tmpDate = QDate::fromString(fname.left(10),"yyyy-MM-dd");

        if ( tmpDate.isValid() && tmpDate > begintime && tmpDate < endtime) {
            dir.remove(files[var]);
        }else{
            qDebug()<<"@del fail";
        }
    }

}

void EasyLog::openLog()
{
//    // 进行日期对比；查看是否要新建一个日志
    QString sDate = QDateTime::currentDateTime().toString("yyyy_MM_dd");
    if (m_fileDate != sDate)
    {
        this->m_fileDate = sDate;
    }
}

EasyLog::EasyLog()
{

}

EasyLog::~EasyLog()
{
#ifdef LOGHTML
    endLogHtml();
#endif
}

EasyLog &EasyLog::getInstance()
{
    return instance;
}

void EasyLog::writeLogHtml(QString _log, QString _details, int _flag)
{
    QString time = QTime::currentTime().toString("hh:mm:ss");
    m_mutex.lock();
    if (_flag == LOG_INFO)
    {
       m_stream << "<br><font size=\"3\" color=\"#459EF6\"family= \"微软雅黑\">" << "Index: "<<m_index << "  Time-->" << time << " " <<  _details<< _log<< "</font>";
    }
    else  if (_flag == LOG_WARNING)
    {
       m_stream << "<br><font size=\"3\" color=\"#0000FF\"family= \"微软雅黑\">" << "Index: "<<m_index << "  Time-->" << time << " " << _details << _log<< "</font>";
    }
    else if (_flag == LOG_ERROR)
    {
       m_stream << "<br><font size=\"3\" color=\"#FF0000\"family= \"微软雅黑\">" << "Index: "<<m_index << "  Time-->" << time << " " << _details << _log<< "</font>";
    }
    m_stream.flush();
    m_log.flush();
    m_index += 1;
    m_mutex.unlock();
}

void EasyLog::writeLog(QString _log, QString _details, int _flag)
{

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    m_mutex.lock();
    if (_flag == LOG_INFO)
    {
       m_stream <<"[INFO]"  << " [Index: "<<m_index <<"] " << time << " " <<  _details<< _log<< "\n";
    }
    else  if (_flag == LOG_WARNING)
    {
       m_stream << "[WARN]" << " [Index: "<<m_index <<"] " <<  time << " " << _details << _log<< "\n";
    }
    else if (_flag == LOG_ERROR)
    {
       m_stream << "[ERR]" << " [Index: "<<m_index <<"] "<< time << " " << _details << _log<< "\n";
    }
    m_stream.flush();
    m_log.flush();
    m_index += 1;
    m_mutex.unlock();
}

void EasyLog::endLogHtml()
{
    if (m_log.isOpen())
    {
        m_stream << "</body>";
        m_stream.flush();
        m_log.flush();
        m_log.close();
    }
}
