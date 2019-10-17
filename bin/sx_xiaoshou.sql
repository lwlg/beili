/*
Navicat SQLite Data Transfer

Source Server         : SS
Source Server Version : 30714
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30714
File Encoding         : 65001

Date: 2019-10-17 21:27:57
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for sx_xiaoshou
-- ----------------------------
DROP TABLE IF EXISTS "main"."sx_xiaoshou";
CREATE TABLE "sx_xiaoshou" (
"jysn"  char(10) NOT NULL,
"jytime"  char(30) NOT NULL,
"brand"  char(40),
"zhonglei"  char(40),
"unit"  char(10),
"jyCnt"  integer NOT NULL,
"price"  integer NOT NULL,
"jine"  integer,
"zftype"  char(30) NOT NULL,
"beizhu"  char(100),
PRIMARY KEY ("jytime" ASC)
);
