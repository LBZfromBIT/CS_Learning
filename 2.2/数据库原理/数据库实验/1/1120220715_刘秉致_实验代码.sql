CREATE DATABASE TPCH CHARACTER SET utf8;--以utf8格式创建数据库TPCH

CREATE SCHEMA Sales;--创建模式Sales

USE Sales;--使用模式Sales

/*
建立基本表Region为地区表
RNo 地区号 为主码
RName 地区名
RNote 备注
*/
CREATE TABLE Region
(
    RNo INT NOT NULL UNIQUE,
    RName VARCHAR(5) NOT NULL UNIQUE,
    RNote VARCHAR(20), 
    PRIMARY KEY(Rno)
);


/*
建立基本表Nation为国家表
NNo 国家号 为主码
NName 国家名
RNo 地区号 为外键
NNote 备注
*/
CREATE TABLE Nation
(
    NNo INT NOT NULL UNIQUE,
    NName VARCHAR(20) NOT NULL UNIQUE,
    RNo INT NOT NULL,
    NNote VARCHAR(30),
    PRIMARY KEY(NNo),
    FOREIGN KEY(RNo) REFERENCES Region(RNo)
);

/*
建立基本表Supplier为供应商基本表
SNo 供应商编号 为主码
SName 供应商名称
SAdress 供应商地址
NNo 国家编号 为外键
STel 供应商电话
*/

CREATE TABLE Supplier
(
    SNo INT NOT NULL UNIQUE,
    SName VARCHAR(30) NOT NULL,
    SAdress VARCHAR(50) NOT NULL,
    NNo INT NOT NULL,
    STel VARCHAR(15) NOT NULL,
    PRIMARY KEY(SNo),
    FOREIGN KEY(NNo) REFERENCES Nation(NNo)
);

/*
建立基本表Part为零件基本表
PNo 零件编号 为主码
PName 零件名称
PProduct 零件制造商
PSize  零件尺寸
PCost 零售价格
*/
CREATE TABLE Part
(
    PNo INT NOT NULL UNIQUE,
    PName VARCHAR(50) NOT NULL,
    PProduct VARCHAR(30) NOT NULL,
    PSize VARCHAR(30),
    PCost INT NOT NULL,
    PRIMARY KEY(PNo)
);

/*
建立关系：零件供应联系表PartSupp
PNo 零件编号 为外码
SNo 供应商编号 为外码
上两个属性组合为主键
Quantity 可用数量
Cost 供应价格
*/
CREATE TABLE PartSupp
(
    PNo INT NOT NULL,
    SNo INT NOT NULL,
    Quantity INT NOT NULL,
    Cost FLOAT NOT NULL,
    PRIMARY KEY(PNo,SNo),
    FOREIGN KEY(PNo) REFERENCES Part(PNo),
    FOREIGN KEY(SNo) REFERENCES Supplier(SNo)
);

/*
建立基本表Customer为顾客表
CNo 顾客编号 为主码
CName 顾客名称
NNo 国籍编号 为外码
*/
CREATE TABLE Customer
(
    CNo INT NOT NULL UNIQUE,
    CName VARCHAR(30) NOT NULL,
    NNo INT NOT NULL,
    PRIMARY KEY(CNo),
    FOREIGN KEY(NNo) REFERENCES Nation(NNo)
);


/*
建立关系表Orders为订单表
ONo 订单编号 为主码
CNo 顾客编号 为外码
ODate 订单日期 
OPrice 订单总金额
*/
CREATE TABLE Orders
(
    ONo INT NOT NULL UNIQUE,
    CNo INT NOT NULL,
    ODate VARCHAR(10) NOT NULL,
    OPrice FLOAT NOT NULL,
    PRIMARY KEY(ONo),
    FOREIGN KEY(CNo) REFERENCES Customer(CNo)
);

/*
建立关系表Lineitem为订单明细表
ONo 订单编号 为外码
PNo 零件编号 为外码
SNo 供应商编号 为外码
以上三个属性为主码
Amount 数量
Refund 退货标记 
Discount 折扣
*/
CREATE TABLE Lineitem
(
    ONo INT NOT NULL,
    PNo INT NOT NULL,
    SNo INT NOT NULL,
    Amount INT NOT NULL,
    Refund INT NOT NULL CHECK(Refund IN(0,1)),
    Discount FLOAT NOT NULL CHECK(Discount BETWEEN 0 AND 1),
    PRIMARY KEY(ONo,PNo,SNo),
    FOREIGN KEY(ONo) REFERENCES Orders(ONo),
    FOREIGN KEY(PNo) REFERENCES Part(PNo),
    FOREIGN KEY(SNo) REFERENCES Supplier(SNo)
);

/*
将数据导入各基本表
语法格式：
LOAD DATA INFILE ‘文件路径’
INTO TABLE 表名 CHARACTER SET 编码格式
FIELDS TERMINATED BY ‘列分隔符’
OPTIONALLY ENCLOSED BY ‘去重符’
ESCAPED BY ‘忽略符’
LINES TERMINATED BY ‘元组分隔符’
*/
LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/region.csv'
INTO TABLE Region CHARACTER SET gb2312
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/nation.csv'
INTO TABLE Nation CHARACTER SET gb2312
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/supplier.csv'
INTO TABLE Supplier CHARACTER SET gbk
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/part.csv'
INTO TABLE Part CHARACTER SET gb18030
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/partsupp.csv'
INTO TABLE PartSupp CHARACTER SET gb2312
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/customer.csv'
INTO TABLE Customer CHARACTER SET gb18030
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/orders.csv'
INTO TABLE Orders CHARACTER SET gb2312
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/1ExpSet/lineitem.csv'
INTO TABLE Lineitem CHARACTER SET gb2312
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
ESCAPED BY '"'
LINES TERMINATED BY '\r\n';
