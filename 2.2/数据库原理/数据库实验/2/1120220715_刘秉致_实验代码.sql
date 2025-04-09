--1）查询所有供应商的名称、地址、联系电话
SELECT SName,SAdress,STel
FROM Supplier;

--2）查询2014年1~10月间的总价大于1000元的订单的编号、顾客编号等订单的所有信息
SELECT * FROM orders WHERE OPrice>1000
AND (LEFT(ODate,6) IN ('2014/1','2014/2','2014/3','2014/4','2014/5','2014/6','2014/7','2014/8','2014/9')
OR LEFT(ODate,7)='2014/10');

--3）统计每个顾客的订购金额
SELECT CNo,SUM(OPrice) AS Total_Price
FROM orders
GROUP BY CNo
ORDER BY CNo;

--4)查询订单平均金额超过1000元的顾客编号及其姓名
SELECT customer.CNo,CName,AVG(OPrice) AS AVG_Price
FROM customer,orders
WHERE customer.CNo=orders.CNo 
GROUP BY CNo
HAVING AVG(OPrice)>1000
ORDER BY CNo;

--5）查询与“金仓集团”在同一个国家的供应商编号、名称和地址信息
SELECT SNo,SName,SAdress 
FROM supplier 
WHERE NNo =
(
    SELECT NNo
    FROM supplier
    WHERE SName='金仓集团'
);

--6）查询供应价格大于零售价格的零件名、制造商名、零售价格和供应价格
SELECT PName,PProduct,PCost,Cost 
FROM part,partsupp
WHERE part.PNo=partsupp.PNo AND PCost<Cost;

--7）查询顾客“阿波罗”订购的订单编号、总价及其订购的零件编号
SELECT orders.ONo,OPrice,PNO 
FROM orders,lineitem
WHERE orders.ONo=lineitem.ONo AND
orders.CNo IN 
(SELECT CNo FROM customer WHERE CName='阿波罗');