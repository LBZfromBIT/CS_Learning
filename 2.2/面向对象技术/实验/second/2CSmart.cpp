#include <iostream>
#include <cstdio>
#include <cstdlib> 
using namespace std;

class CSmart{
    private:
    bool live;
    static int sum;
    public:
    CSmart(){
        live=true;
        sum++;
        if(sum==1||sum==0){
            cout<<sum<<" object"<<endl;
        }
        else{
            cout<<sum<<" objects"<<endl;
        }
    }
    ~CSmart(){
        if(live==true){
            sum--;
            live=false;
            if(sum==1||sum==0){
                cout<<sum<<" object"<<endl;
            }
            else{
                cout<<sum<<" objects"<<endl;
            }
        }
    }
};
int CSmart::sum=0;

void DoSomething(){
    CSmart s;
}
CSmart s1;//add s1,1 obj
int main(){
    CSmart s2;//add s2,2 obj
    DoSomething();//add s,3 objs
    //函数作用域外，delete s,2 objs
    CSmart* s3=new CSmart;//add s3,3 objs
    delete s3;//delete s3,2objs
    s2.~CSmart();//手动调用析构函数，s2内存未被释放,s2对象仍存在
    return 0;
    //delete s2,1 obj
    //delete s1,0 obj
}
