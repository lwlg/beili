#ifndef DB_SQL
#define DB_SQL

#define DataPath_XSFile "/sx.db"

#define XS_CreateDB "CREATE TABLE sx_xiaoshou ( jysn char(10) NOT NULL, jytime char(30) NOT NULL, brand char(40) NULL, zhonglei char(40) NULL, unit char(10) NULL, jyCnt integer NOT NULL, price integer NOT NULL, jine  integer NULL,	 zftype integer NULL, beizhu char(100) NULL, PRIMARY KEY (jytime) )"


#define XS_Insert  "insert into sx_xiaoshou (jysn,jytime,brand,zhonglei,unit, jyCnt,price,  jine, zftype,  beizhu  ) " \
    "values ('%s','%s','%s','%s','%s','%d','%d','%d','%s','%s')"

#define XS_SelectAll  "SELECT jysn,jytime,brand,zhonglei,unit,jyCnt,0.01*price,0.01*jine,zftype,beizhu FROM sx_xiaoshou"

#define XS_Select  "SELECT jysn,jytime,brand,zhonglei,unit,jyCnt,0.01*price,0.01*jine,zftype,beizhu FROM sx_xiaoshou "\
                   "WHERE (beizhu like '%%%s%') OR (jytime > '%s' and jytime <'%s')"


//进货库存表
#define JH_CreateDB  "CREATE TABLE sx_jinhuo(inCnt integer NOT NULL,GoodsCode char(15) NOT NULL, "\
                     "GoodName char(30) NOT NULL, GoodsBrand char(40) NULL, "\
                     "xinghao char(40) NULL, unit char(10) NULL, inCnt integer NOT NULL, "\
                     "price integer NOT NULL, jine  integer NULL,"\
                     "changjia char(40) NULL, intime char(30) NULL,beizhu char(100) NULL ,PRIMARY KEY (jytime))"


//价格查询
#define JH_PriceQuery  "SELECT * FROM sx_jinhuo WHERE (GoodCode like '%%%s%') and (GoodSupplier like '%%%s%')"

//插入数据
#define JH_Inser   "insert into sx_jinhuo (GoodCode,GoodName,GoodBrand,GoodType,GoodUnit,GoodInCnt,GoodPrice, GoodMoney, GoodSupplier,GoodInTime ,Memo) " \
                         "values ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"


//删除数据
#define JH_Del   "DELETE FROM sx_jinhuo WHERE id='%s'"


//更新数据
#define JH_Update "UPDATE sx_jinhuo SET GoodCode = '%s',"\
                  "GoodName='%s',GoodBrand='%s',"\
                  "GoodType='%s',GoodUnit='%s',"\
                  "GoodInCnt='%s',GoodPrice='%s',"\
                  "GoodMoney='%s',GoodSupplier='%s',"\
                  "GoodInTime='%s',Memo='%s'"\
                  "WHERE ID='%s'"
#endif // DB_SQL


