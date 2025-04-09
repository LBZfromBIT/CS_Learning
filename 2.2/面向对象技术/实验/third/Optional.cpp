#include <iostream>
#include <string>
using namespace std;

class CLINT{
    private:
        int* arr;
        int size;
    public:
        CLINT();
        CLINT(string s);
        CLINT& operator = (const CLINT& L);
        ~CLINT();
        CLINT Add(const CLINT& L);//Achieve the sum of two big numbers
        void Value();//Display the big number
};
//the constructor function
CLINT::CLINT(){
    size=0;
    arr=new int[105];
}
CLINT::CLINT(string s){
    size=s.length();
    arr=new int[105];
    for(int i=0,ptr=size-1;i<size&&ptr>=0;i++,ptr--){
        arr[i]=s[ptr]-'0';//store in backwards
    }
}
//the destructor function
CLINT::~CLINT(){
    if(arr!=nullptr){
        delete[] arr;
    }
}
/*the operator function which avoid when some object is copied by others 
and because their is a pointer in member var which may lead memory leak*/
CLINT& CLINT::operator=(const CLINT& L){
    if(this!=&L){
        this->size=L.size;
        if(L.arr!=nullptr){
            this->arr=new int[105];
            for(int i=0;i<L.size;i++){
                this->arr[i]=L.arr[i];
            }
        }
    }
    return *this;
}
//the add function
CLINT CLINT::Add(const CLINT& L){
    CLINT ans;
    bool flag=false;
    int i;
    for(i=0;i<size&&i<L.size;i++){
        int temp=arr[i]+L.arr[i];
        if(flag==true){
            temp++;
        }
        if(temp>=10){
            flag=true;
            temp=temp-10;
        }
        ans.arr[i]=temp;
        ans.size++;
    }
    if(i<size){//L is empty
        for(;i<size;i++){
            int temp=arr[i];
            if(flag==true){
                temp++;
            }
            if(temp>=10){
                temp=temp-10;
                flag=true;
            }
            ans.arr[i]=temp;
            ans.size++;
        }
    }
    if(i<L.size){//this is empty
       for(;i<L.size;i++){
            int temp=L.arr[i];
            if(flag==true){
                temp++;
            }
            if(temp>=10){
                temp=temp-10;
                flag=true;
            }
            ans.arr[i]=temp;
            ans.size++;
        }
    }
    if(flag==true){
        ans.arr[ans.size]=1;
        ans.size++;
    }
    return ans;
}

//the display function
void CLINT::Value(){
    for(int i=size-1;i>=0;i--){
        cout<<arr[i];
    }
    cout<<endl;
}

int main(){
    CLINT L1("12345678900987654321"),L2("9876543210"),L3;
    L3=L1.Add(L2);
    L3.Value();
    return 0;
}