#ifndef EASYLOG_H
#define EASYLOG_H

#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <stdio.h>



#define LOG_INFO        0
#define LOG_WARNING     1
#define LOG_ERROR       2

//#define LOGHTML 1    //comment enable html log,uncomment normal log

#define EasyLOG EasyLog::getInstance()
#define DETAIL_INFO  QString::fromLocal8Bit("<.%1.>@%2=>%3:   ").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__)


#ifdef LOGHTML
#define LOG_IDENTIFIER "_Log.html"
#define LOGERROR(_log)   EasyLOG.writeLogHtml(_log, DETAIL_INFO, LOG_ERROR)
#define LOGINFO(_log)    EasyLOG.writeLogHtml(_log, DETAIL_INFO, LOG_INFO)
#define LOGWRANING(_log) EasyLOG.writeLogHtml(_log, DETAIL_INFO, LOG_WARNING)
#define LOGINIT()        EasyLOG.InitLogHtml()
#else
#define LOG_IDENTIFIER "_Log.log"
#define LOGERROR(_log)   EasyLOG.writeLog(_log, DETAIL_INFO, LOG_ERROR)
#define LOGINFO(_log)    EasyLOG.writeLog(_log, DETAIL_INFO, LOG_INFO)
#define LOGWRANING(_log) EasyLOG.writeLog(_log, DETAIL_INFO, LOG_WARNING)
#define LOGINIT()        EasyLOG.InitLog()
#endif


class EasyLog
{
private:
    EasyLog();

    static EasyLog instance;
public:
    ~EasyLog();

    static EasyLog&   getInstance();

    void writeLogHtml(QString _log, QString _details = "", int _flag = LOG_INFO);

    void writeLog(QString _log, QString _details = "", int _flag = LOG_INFO);

    void InitLogHtml();
    void InitLog();
    
private:
    void openLog();
    void endLogHtml();
private:
    QString             m_fileDate;
    QFile               m_log;
    QMutex              m_mutex;
    QTextStream         m_stream;
    int                 m_index;
};
#endif // EASYLOG_H
