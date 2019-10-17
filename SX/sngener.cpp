#include "sngener.h"
#include "EasyLog.h"
#include "common.h"
int SNGener::cnt = 0;
QString SNGener::m_fileDate = "";

SNGener::SNGener()
{

}

void SNGener::readCnt()
{
    //当日,读取cnt
    m_fileDate = theIni.getStrImp("SN/datetime");

    QString sDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    if (m_fileDate != sDate)
    {
        m_fileDate = sDate;
        return;
    }
    //当日,读取cnt
    cnt = theIni.getStrImp("SN/XS_SN").toInt();
    LOGINFO(QString::asprintf("读取数据>>%d",cnt));
}

void SNGener::saveCnt()
{
    theIni.getStrImp("SN/XS_SN",QString::number(cnt));

    theIni.getStrImp("SN/datetime",m_fileDate);

    LOGINFO(QString::asprintf("保存数据成功>>%d,%s",cnt,C_STR(m_fileDate)));
}


int SNGener::getSN()
{
    if(cnt>999999)
        cnt =0 ;

    return cnt++;
}

