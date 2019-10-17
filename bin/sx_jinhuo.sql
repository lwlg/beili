/*
Navicat SQLite Data Transfer

Source Server         : SS
Source Server Version : 30714
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30714
File Encoding         : 65001

Date: 2019-10-17 21:27:48
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for sx_jinhuo
-- ----------------------------
DROP TABLE IF EXISTS "main"."sx_jinhuo";
CREATE TABLE "sx_jinhuo" (
"ID"  INTEGER NOT NULL,
"GoodCode"  TEXT,
"GoodName"  TEXT,
"GoodBrand"  TEXT,
"GoodType"  TEXT,
"GoodUnit"  TEXT,
"GoodInCnt"  TEXT,
"GoodPrice"  TEXT,
"GoodMoney"  TEXT,
"GoodSupplier"  TEXT,
"GoodInTime"  TEXT,
"Memo"  TEXT,
PRIMARY KEY ("ID")
);
