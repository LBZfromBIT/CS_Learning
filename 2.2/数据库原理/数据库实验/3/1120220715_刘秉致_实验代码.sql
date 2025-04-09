use sales;

/*（1）查询订购了“徐州市泰力公司矿山设备四厂”制造的“活塞式减压阀”的顾客的信息*/
SELECT * FROM customer WHERE CNo IN
(SELECT CNo FROM orders WHERE ONo IN
    (SELECT ONo FROM lineitem WHERE PNo IN
        (SELECT Pno FROM part WHERE Pname="活塞式减压阀" 
            AND PProduct="徐州市泰力公司矿山设备四厂")
    )
);

/*（2）查询没有购买过“徐州市泰力公司矿山设备四厂”制造的“活塞式减压阀”的顾客的信息*/
SELECT * FROM customer WHERE CNo NOT IN/*求差操作*/
(SELECT CNo FROM orders WHERE ONo IN
    (SELECT ONo FROM lineitem WHERE PNo IN
        (SELECT Pno FROM part WHERE Pname="活塞式减压阀" 
            AND PProduct="徐州市泰力公司矿山设备四厂")
    )
);

/*（3）查询订单平均金额超过500元的顾客中的中国籍顾客的信息*/
SELECT * FROM customer 
/*由于数据库中录入信息时国家名后的空格没有截断，只能采用字符串匹配查找*/
WHERE NNo IN (SELECT NNo FROM nation WHERE NName LIKE "中国%")
AND Cno IN(
    /*按Cno分组并在每个组内使用集函数判断平均金额*/
    SELECT CNo FROM orders GROUP BY (CNo) 
        HAVING AVG(OPrice)>500
);

/* (4) 查询顾客“薜融”订购过而“宣荣揣”没有订购过的零件的信息*/
SELECT * FROM part WHERE PNo IN
(
    (SELECT PNo FROM lineitem WHERE ONo IN
        (SELECT ONo FROM orders WHERE CNo IN 
            (SELECT CNo FROM customer WHERE CName="薜融")
        )
    )
    EXCEPT/*需要求两个集合的差集*/
    (SELECT PNo FROM lineitem WHERE ONo IN
        (SELECT ONo FROM orders WHERE CNo IN 
            (SELECT CNo FROM customer WHERE CName="宣荣揣")
        )
    ) 
); 

/*（1）	在Lineitem表上定义一个INSERT触发器，
    当增加一项订单明细时，自动修改订单表Orders中的订单总金额，
    以保持数据的一致性。（增加的那一部分金额为：零售价×数量×折扣）
*/
CREATE TRIGGER self_update AFTER INSERT 
ON lineitem FOR EACH ROW
BEGIN 
   /*由于插入记录内无零售价格，因此内嵌一个查询，获取零售价格*/
    UPDATE orders SET OPrice=OPrice+(NEW.Amount*NEW.Discount*(SELECT PCost FROM part WHERE PNo=NEW.PNO))
    WHERE orders.ONo=NEW.ONo;
END;


/*建立测试事务1*/
START TRANSACTION;
/*先查询订单编号为1的订单的相关信息和和查询lineitem表中订单编号为1的订单明细*/
SELECT * FROM orders WHERE ONo=1;
SELECT * FROM lineitem WHERE ONo=1; 
/*在lineitem表中插入一条记录,订单1中补充订购1号零件，折扣为0.9，数量100*/
INSERT INTO lineitem VALUES(1,1,1,100,0,0.9);
/*再查询订单编号为1的订单的相关信息和查询lineitem表中订单编号为1的订单明细*/
SELECT * FROM orders WHERE ONo=1;
SELECT * FROM lineitem WHERE ONo=1;
ROLLBACK;

/*（2）	在Lineitem表上定义一个BEFORE UPDATE触发器，
    当修改订单明细中的数量时，先检查零件供应表PartSupp中的可用数量是否足够。*/
CREATE TRIGGER enough_check BEFORE UPDATE
ON lineitem FOR EACH ROW
BEGIN
     /*先看是否增多*/
     IF(NEW.Amount>OLD.Amount) THEN
        /*再看是否足够*/
        IF(NEW.Amount>(SELECT Quantity FROM partsupp WHERE (PNo=NEW.PNo AND SNo=NEW.SNo))) THEN
        /*mySQL中无法直接打印字符串，因此只能自行定义错误信息并返回*/
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "NOT ENOUGH";
        END IF;
    END IF;
END;

/*建立测试事务2*/
START TRANSACTION;
/*先查询订单编号为5426的订单的相关信息和其中所有的零件的可用容量*/
SELECT * FROM lineitem WHERE ONo=5426;
SELECT * FROM partsupp WHERE PNo IN(SELECT PNo FROM lineitem WHERE ONo=5426);  
/*更改由供应商编号为11642、零件编号为2的数量为1000*/
UPDATE lineitem SET Amount=1000 WHERE (ONo=5426 AND Pno=2 AND SNo=11642);
ROLLBACK;         