本文档旨在对题目1的类的设置和函数接口的含义进行解释

1.类的设置
本程序的类可以分为以下几类：
a.人员类 
   包含基类People和两个派生类Student和Teacher，每个类的实例对应一个人，其主键为ID
b.课程类
   包含一个类Class，每个类的实例对应一个课程，其主键为CID，即课程ID
c.记录类
   包含一个类Record,每个类的实例对应一个记录，其主键为SID+CID,即学生ID+课程ID

在以上几个类的基础上，为每个类定义一个集合类（SSet,TSet,CSet,RSet),用来储存当前存在的各个实例
最终，为所有数据的存储设置Database类，内部组合了各集合类（SSet,TSet,CSet,RSet)用来存储各实例并在该类的成员函数中实现各操作接口

2.函数的解释
void GetTeacherByCourse( string SID,string CID)
参数：SID指定当前查询的学生，CID指定查询的课程
功能：实现学生凭借自身ID和课程的ID查询自己所选课程的授课教师姓名，并拒绝查询其他课程的老师

void GetScoreByCourse(string SID,string CID)
参数：SID指定当前查询的学生，CID指定查询的课程
功能：实现学生凭借自身ID和课程的ID查询自己所选课程的成绩

void  GetStudInfoByID( string TID,string SID)
参数：TID指定当前查询的老师，SID指定查询的学生
功能：实现教师凭借自身ID和学生ID查询自己教学班内学生的信息，并且拒绝查询其他班级的学生信息

 void SetScoreToCourse(string TID,string SID,string CID,int g)
参数：TID指定当前查询的老师，SID指定查询的学生，CID指定查询的课程，g指定成绩
功能：实现教师对自己所教学班级内学生的成绩进行重设或添加，并且拒绝修改其他课程和学生的成绩