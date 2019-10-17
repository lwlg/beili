#ifndef DATARECORD
#define DATARECORD

#include <QString>
#include <QDateTime>
#include "common.h"
#include "db_sql.h"
//#include "inisettings.h"
//#include "SXGlobal.h"
#include "sngener.h"


//序列号生成器
//class SNGener
//{
//public:
//    SNGener() {}

////    static int getSN()
////    {
////       static int cnt = 0;

////       if(cnt>999999)
////            cnt =0 ;

////       return cnt++;
////    }

//    static int getSN()
//    {
////        if(cnt>999999)
////            cnt =0 ;

//        return cnt++;
//    }

//    int getCnt()
//    {
//        return cnt;
//    }

//    static void saveCnt()
//    {
////        theIni.getStrImp("SN/XS_SN",QString::number(cnt));
//    }

//    static void readCnt()
//    {
////        cnt = theIni.getStrImp("SN/XS_SN").toInt();
////        lwlgout<<"cnt="<<cnt;
//    }

//protected:
//   static int cnt;
//};
////int SNGener::cnt=0;


//对应表中字段
struct XS_Tab{
    QString      jysn;
    QString      jytime;
    QString      brand;
    QString      zhonglei;
    QString      unit;
    int          jyCnt;
    int          price;//分
    int          jine;//分
    //int          zftype;
    QString          zftype;
    QString      beizhu;

    XS_Tab(){
        this->jysn     = "";
        this->jytime   = "";
        this->brand    = "";
        this->zhonglei = "";
        this->unit     = "";
        this->jyCnt    = 0;
        this->price    = 0;
        this->jine     = 0;
        this->zftype   = "";

        this->beizhu   = "";
    }

   static QString getjySn()
    {

//        QString _sn = QDateTime::currentDateTime().toString(DATETIME_STYLE_2) +
//                      "_" + QString::number(SNGener::getSN());


//        int nSn = theIni.getStrImp("SN/XS_SN").toInt();

        QString _sn = QDateTime::currentDateTime().toString(DATETIME_STYLE_2) +
                "_" + QString::number(SNGener::getSN());

        return _sn;
    }

   static QString getjytime()
    {
        return  QDateTime::currentDateTime().toString(DATETIME_STYLE);
    }

    int getJine()
    {
        return this->jyCnt * this->price;
    }

    QString toInsertSql(){
        return QString::asprintf(XS_Insert, C_STR(jysn), C_STR(jytime),C_STR(brand),
                                 C_STR(zhonglei),C_STR(unit),
                                 jyCnt,price,jine,C_STR(zftype), C_STR(beizhu));
    }

    QString toSelSql(QString beginTime,QString endTime)
    {
        return QString::asprintf(XS_Select, C_STR(beginTime),C_STR(endTime));
    }

};

///
/// 进货明细
///
struct JH_Tab{

//    QString ID;
    QString GoodCode;
    QString GoodName;
    QString GoodBrand;
    QString GoodType;
    QString GoodUnit;
    QString GoodCnt;
    QString Goodprice;
    QString Goodjine;
    QString Goodsupplier;
    QString Goodintime;
    QString GoodMemo;

    QString toSelSql(QString goodCode)
    {
        return QString::asprintf(JH_PriceQuery, C_STR(goodCode));
    }

};

#endif // DATARECORD

