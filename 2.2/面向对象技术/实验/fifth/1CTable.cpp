/*
To understand the struct of these set and their relationship
please read the README.txt in the file 
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

/*category one:
  People(base)——to store info of each person
  |---Student(derived)
        |---SSet——the student set
  |---Teacher(derived)
        |---TSet——the teacher set
*/
class People
{
    private:
        string name;
        string ID;
        string birth;
        string gender;
    public:
        People(string n,string g,string b,string I){
            name=n;
            ID=I;
            gender=g;
            birth=b;
        }
        string getname(){return name;}
        string getID(){return ID;}
        string getgender(){return gender;}
        string getbirth(){
            return birth;
        }
        void reset(string n,string g,string b,string I){
            name=n;
            ID=I;
            gender=g;
            birth=b;
        }
        void show (){
            cout<<"name: "<<getname()<<" gender: "<<getgender()<<" birth: "<<getbirth()<<" ID: "<<getID()<<endl;
        }
};

class Student:public People
{
    public:
        Student(string n,string g,string b,string I):People(n,g,b,I){
            cout<<"student "<<getID()<<" created."<<endl;
        }
};

class Teacher:public People
{
    public:
        Teacher(string n,string g,string b,string I):People(n,g,b,I){
            cout<<"teacher "<<getID()<<" created."<<endl;
        }
};

template <typename T>
class PeoSet
{
    private:
        vector<T> peo;
    public:
        int IsIn(string SID){//return index or -1
            if(peo.empty()!=true){
                for(int i=0;i<peo.size();i++){
                    if(peo[i].getID()==SID){
                        return i;
                    }
                }
                return -1;
            }
            else{
                return -1;
            }
        }
        void Add(T s){
            //not allow repeat
            if(IsIn(s.getID())!=-1){
                return ;
            }
            peo.push_back(s);
        }
        void Remove(string SID){
            int index=IsIn(SID);
            if(index!=-1){
                peo.erase(peo.begin()+index);
            }
        }
        T& operator [](int i){
            return peo[i];
        }
};



/*category two:
  Class——to store the info of each class
  |---Cset 
*/
class Class
{
    private:
        string name;
        string ID;
        string tID;
    public:
        Class(string I,string n,string t){
            name=n;
            ID=I;
            tID=t;
            cout<<"class "<<getID()<<" created."<<endl;
        }
        string getname(){return name;}
        string getID(){return ID;}
        string gettID(){return tID;}
        void reset(string n,string i,string t){
            name=n;
            ID=i;
            tID=t;
        }
};

class CSet
{
    private:
        vector<Class> cla;
    public:
        int IsIn(string CID){//return index or -1
            if(cla.empty()!=true){
                for(int i=0;i<cla.size();i++){
                    if(cla[i].getID()==CID){
                        return i;
                    }
                }
                return -1;
            }
            else{
                return -1;
            }
        }
        void Add(Class s){
            //not allow repeat
            if(IsIn(s.getID())!=-1){
                return ;
            }
            cla.push_back(s);
        }
        void Remove(string CID){
            int index=IsIn(CID);
            if(index!=-1){
                cla.erase(cla.begin()+index);
            }
        }
        Class& operator[](int i){
            return cla[i];
        }
};

/*category three:
  Record——to store the info of each record
  |---Rset
*/
class Record
{
    private:
        string sID;
        string cID;
        int grade;
    public:
        Record(string s,string c,int g){
            sID=s;
            cID=c;
            grade=g;
            cout<<"Record created."<<endl;
        }
        string getsID(){return sID;}
        string getcID(){return cID;}
        int getgrade(){return grade;}
        void reset(string s,string c,int g){
            sID=s;
            cID=c;
            grade=g;
        }
};

class RSet
{
    private:
        vector<Record> rec;
    public:
        int IsIn(string SID,string CID){
            if(rec.empty()!=true){
                for(int i=0;i<rec.size();i++){
                    if(rec[i].getcID()==CID&&rec[i].getsID()==SID){
                        return i;
                    }
                }
                return -1;
            }
            else{
                return -1;
            }
        }
        void Add(Record s){
            //not allow repeat
            if(IsIn(s.getsID(),s.getcID())!=-1){
                return ;
            }
            else{
                rec.push_back(s);
            }
        }
        void Remove(string SID,string CID){
            int index=IsIn(SID,CID);
            if(index!=-1){
                rec.erase(rec.begin()+index);
            }
        }
        void Set(string SID,string CID,int g){
            int index=IsIn(SID,CID);
            if(index!=-1){
                rec[index].reset(SID,CID,g);
            }        
        }
        Record& operator [](int i){
            return rec[i];
        }
};

//the final class: database table
class Database
{
    private:
        PeoSet<Student> sset;
        PeoSet<Teacher> tset;
        CSet cset;
        RSet rset;
    public:
        void AddStudent(Student s){sset.Add(s);}
        void AddTeacher(Teacher t){tset.Add(t);}
        void AddClass(Class c){cset.Add(c);};
        void AddRecord(Record r){rset.Add(r);}
        void RemoveStudent(string ID){sset.Remove(ID);}
        void RemoveTeacher(string ID){tset.Remove(ID);}
        void RemoveClass(string ID){cset.Remove(ID);}
        void RemoveRecord(string SID,string CID){rset.Remove(SID,CID);}
        void GetTeacherByCourse( string SID,string CID){
            if(sset.IsIn(SID)==-1){
                cout<<"your id is not exist."<<endl;
                return;
            }
            else if(cset.IsIn(CID)==-1){
                cout<<"class not exsit."<<endl;
                return;
            }
            else if(rset.IsIn(SID,CID)==-1){
                cout<<"you are not in the class."<<endl;
                return;
            }
            else{
                int index=cset.IsIn(CID);
                string tid=cset[index].gettID();
                index=tset.IsIn(tid);
                if(index==-1){
                    cout<<"teacher not exist."<<endl;
                    return ;
                }
                cout<<"teacher: "<<tset[index].getname()<<endl;
                return;
            }
        }
        void GetScoreByCourse(string SID,string CID){
            if(sset.IsIn(SID)==-1){
                cout<<"your id is not exist."<<endl;
                return;
            }
            else if(cset.IsIn(CID)==-1){
                cout<<"class not exsit."<<endl;
                return;
            }
            else if(rset.IsIn(SID,CID)==-1){
                cout<<"you are not in the class."<<endl;
                return;
            }
            else{
                int index=rset.IsIn(SID,CID);
                cout<<"your score is "<<rset[index].getgrade()<<endl;
                return;
            }
        }
        void  GetStudInfoByID( string TID,string SID){
            if(tset.IsIn(TID)==-1){
                cout<<"your ID is not exist."<<endl;
                return;
            }
            else if(sset.IsIn(SID)==-1){
                cout<<"Student not exist."<<endl;
                return;
            }
            else{
                int index=sset.IsIn(SID);
                Student temp=sset[index];
                temp.show();
                return;
            }
        }
        void SetScoreToCourse(string TID,string SID,string CID,int g){
            if(tset.IsIn(TID)==-1){
                cout<<"your ID is not exist."<<endl;
                return;
            }
            else if(sset.IsIn(SID)==-1){
                cout<<"student not exist."<<endl;
                return;
            }
            else if(cset.IsIn(CID)==-1){
                cout<<"class not exist."<<endl;
                return;
            }
            else{
                int index=cset.IsIn(CID);
                string temp=cset[index].gettID();
                if(TID!=temp){
                    cout<<"you are not allow to change this class."<<endl;
                    return;
                }
                else{
                    if(rset.IsIn(SID,CID)==-1){
                        Record an(SID,CID,g);
                        rset.Add(an);
                        cout<<"put in successfully."<<endl;
                        return;
                    }
                    else{
                        rset.Set(SID,CID,g);
                        cout<<"reset successfully."<<endl;
                        return;
                    }
                }
            }
        }
};

int  main(){
    Student s1("李逵","男","2000.8","20200801");
    Student s2("花千羽","女","2003.10","20221011");
    Student s3("TF-BOY","男","2004.9","20210901");
    Student s4("冷冰冰","女","2004.8","20221217");
    Teacher t1("孙悟空","男","1965.8","t20011211");
    Teacher t2("张三丰","男","1979.10","t20060708");
    Class c1("COM002","自然语言理解","t19971211");
    Class c2("COM006","面向对象技术与方法","t20060708");
    Class c3("COM016","大数据处理","t20160708");
    Record r1("20200801","COM002",86);
    Record r2("20221011","COM006",97);
    Record r3("20210901","COM016",90);
    Record r4("20221217","COM006",79);
    Database db;
    db.AddStudent(s1);
    db.AddStudent(s2);
    db.AddStudent(s3);
    db.AddStudent(s4);
    db.AddTeacher(t1);
    db.AddTeacher(t2);
    db.AddClass(c1);
    db.AddClass(c2);
    db.AddClass(c3);
    db.AddRecord(r1);
    db.AddRecord(r2);
    db.AddRecord(r3);
    db.AddRecord(r4);

    db.GetScoreByCourse("20200801","COM002");
    db.GetScoreByCourse("20200801","COM003");

    db.GetStudInfoByID("t20060708","20200801");
    db.GetStudInfoByID("t20060708","20221111");

    db.GetTeacherByCourse("20200801","COM002");
    db.GetTeacherByCourse("20200801","COM006");

    db.SetScoreToCourse("t20060708","20200801","COM002",99);
    db.SetScoreToCourse("t20060708","20221217","COM006",99);
}