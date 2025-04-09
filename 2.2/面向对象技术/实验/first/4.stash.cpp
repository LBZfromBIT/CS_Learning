#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cassert>
using namespace std;

class Stash{
    private:
        int size;//size of each space
        int quantity;//number of storage spaces
        int next;//next empty space
        unsigned char* storage;//dynamically allocated storage
    public:
        Stash(int ssize,int squantity);
        //skip the init function by using above function
        ~Stash();
        void cleanup();
        int add(const void* element);
        void* fetch(int index);
        int count();
        void inflate(int increase);//we set the basic increasement 200
        void remove(int index);
        void contract(int decrease);
};
//the init function 
Stash::Stash(int ssize=1,int squantity=100){
    size=ssize;
    quantity=squantity;
    next=0;
    storage=new unsigned char [quantity*size];//we set the basic storage 100
    cout<<"init done."<<endl;
}
//the destuct function
Stash::~Stash(){
    cout<<"stash detroyed."<<endl;
    delete[] storage;
}
//the cleanup function
void Stash::cleanup(){
    if(storage!=nullptr){
        cout<<"freeing storage."<<endl;
        delete[] storage;
    }
    cout<<"stash destroyed"<<endl;
    return;
}
//the add function,return the index
int Stash::add(const void* element){
    //first check the rest room
   if(next>=quantity){//no room
        inflate(200);
   }
   //start to add
   int startbytes=next*size;
   unsigned char* tmp=(unsigned char*)element;
   for(int i=0;i<size;i++){
    storage[startbytes+i]=tmp[i];
   }
   next++;
   return next-1;
}
//the fetch function,return the poniter which point the index element
void* Stash::fetch(int index){
   assert(index>=0);
   if(index>=next){
        cout<<"nothing there."<<endl;
        return nullptr;
   }
   else{
        return &(storage[index*size]);
   }
}
//the count function
int Stash::count(){
    return next;
}
//the inflate function,we set default 200
void Stash::inflate(int increasement=200){
    assert(increasement>0);
    int newQuantity=quantity+increasement;
    int newBytes=newQuantity*size;
    int oldBytes=next*size;
    //copy
    unsigned char* ns=new unsigned char[newBytes];
    for(int i=0;i<oldBytes;i++){
        ns[i]=storage[i];
    }
    delete[] storage;
    storage=ns;
    quantity=newQuantity;
    return; 
}
//the remove function
void Stash::remove(int index){
    assert(index>=0);
    if(index>=next){
        cout<<"out of range"<<endl;
        return;
    }
    else{
    //remove
        int startplace=index*size;//the removed element start place
        int endplace=startplace+size;//the removed element end place
        int finalplace=next*size;//the place after final element 
        for(int h=startplace,t=endplace;h<finalplace-1&&t<finalplace;h++,t++){//move byte by byte
            storage[h]=storage[t];
            storage[t]=0;
        }
        next--;
        cout<<"done."<<endl;
        if(quantity-next>=200){
            cout<<"too much empty room,contract 100 room automaticlly."<<endl;
            contract(100);
        }
        return;
    }
}
//the contract function,the function will increase 100
void Stash::contract(int decreasement=100){
    assert(decreasement>0);
    if(quantity-next<=decreasement){
        cout<<"no enough room."<<endl;
        return;
    }
    else{
        int newQuantity=quantity-decreasement;
        int newByte=newQuantity*size;
        int oldByte=next*size;
        unsigned char* ns=new unsigned char [newByte];
        for(int i=0;i<oldByte;i++){
            ns[i]=storage[i];
        }
        delete[] storage;
        storage=ns;
        quantity=newQuantity;
        cout<<"done."<<endl;
        return;
    }
}

int main(){
    Stash intarray(100,sizeof(int));
    int p=100;
    intarray.add(&p);
    intarray.count();
    int* place=(int*)intarray.fetch(0);
    cout<<place<<endl;
    intarray.inflate(500);
    intarray.remove(0);
    return 0;
}