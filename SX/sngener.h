#ifndef SNGENER_H
#define SNGENER_H
#include "inisettings.h"
#include "SXGlobal.h"

class SNGener
{
public:
    SNGener();

    static void readCnt();

    static void saveCnt();

    static int getSN();
protected:
   static int cnt;

   static QString m_fileDate;
};

#endif // SNGENER_H
