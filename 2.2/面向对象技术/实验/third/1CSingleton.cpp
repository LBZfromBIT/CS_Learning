/*
该段代码实现了一个简单的单例模式，即在一个程序中仅允许同时出现一个属于Singleton类的对象，
但用户可以通过该类的成员函数获得多个指向该对象的指针，对该对象进行操作
This particular piece of code realizes a basic Singleton design pattern, 
ensuring that there can be only one instance of the Singleton class at any given time in a program. 
Despite this, users are able to obtain several pointers referencing this unique object by means of the class's member functions, 
thereby enabling them to perform various operations on it.
*/
#include <iostream>
using namespace std;
class Singleton{
    private:
    static Singleton *s;//静态指针，指向唯一对象。static pointer which points to the unique object.
    Singleton(){cout<<"Constructor"<<endl;}//私有构造函数，确保用户只能通过成员函数获得实例的指针 the private constructor which make sure the user can only using member function to get the pointer
    Singleton(const Singleton& L);//修改一：私有拷贝构造函数，防止用户自行创建新对象以及潜在的内存泄漏 private copy constructor
    Singleton& operator = (const Singleton& L);//修改二：私有赋值运算符，防止用户自行创建新对象以及潜在的内存泄漏 private assignment operator
    public:
    static Singleton* GetInstance(){//静态成员函数，记录并返回该唯一对象 static member function,records and return the unique object
        if(s==nullptr) s=new Singleton();//当对象为空时，调用构造函数创建一个新对象 when the object is empty,create a new one
        return s;
    }
    ~Singleton(){//析构函数，释放对象 the destructor,relase the object
        if(s!=nullptr){//当s非空时，释放s release s when it's not empty
            delete s;
            cout<<"Release the static s."<<endl;
        }
    }
};
Singleton::Singleton(const Singleton& L){
    if(L.s==nullptr) L.s=new Singleton();
    s=L.s;
}
Singleton& Singleton::operator=(const Singleton& L){
    if(L.s==nullptr) L.s=new Singleton();
    s=L.s;
    return *this;
}
Singleton* Singleton::s=nullptr;//初始化唯一对象 initialization of the unique object
int main(){
    Singleton *ps;
    ps=Singleton::GetInstance();
    cout<<ps<<endl;
    return 0;
}