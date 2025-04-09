use sales;

/*1. 对数据库sales进行备份
    由于MySQL不支持仅使用SQL语句完成数据库的备份和恢复，
    所以此处我们在终端中使用第三方工具MySQLdump来完成数据库的备份   
    注意：请勿使用powershell进行备份，否则会由于编码问题导致备份文件乱码而无法恢复
*/
/*
-u指定数据库用户 -p待输入用户密码 
sales指定要备份的数据库 sales_BP.sql指定备份的文件路径
注意：请在终端中使用该命令*/
mysqldump -u root -p sales > sales_BP.sql



/*2.对数据库sales进行恢复*/
/*先删除数据库sales*/
drop database sales;
show databases;
/*再利用备份文件重建数据库*/
create database sales;
use sales;
source sales_BP.sql;
/*重新查看数据库*/
show databases;

/*3.创建名为“BIT”的新用户；
授权“BIT”查询订单明细表的权限；
授权“BIT”修改订单明细表中折扣的权限；
收回“BIT”的所有权限。
*/
/*创建新用户*/
create user BIT IDENTIFIED BY 'debug1212';
/*授权*/
grant SELECT on lineitem to BIT;
grant UPDATE(Discount) on lineitem to BIT;
/*查看授权*/
show grants for BIT;  
/*收回授权*/
revoke all on sales.lineitem FROM BIT;
/*再看授权*/
show grants for BIT;  
drop user BIT;