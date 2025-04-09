#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;


//the status if the user wants to see the prompt
#define YES true
#define NO false

//the compare function
int compare(const void* a,const void* b){
    return  (*(int*)a)-(*(int*)b);
}

class CSet{//the interger set
    private:/// the member var
    int* storage;//the storage array
    int capacity;//the capacity
    int next;//the next free place
    public://the member functions
    CSet(int cap);
    bool AddCap(int add,bool isShow);
    bool SubCap(int con,bool isShow);
    bool IsExist(int element,bool isShow);
    bool IsEqual(CSet os,bool isShow);
    CSet Intersection(CSet os,bool isShow);
    CSet Union(CSet os,bool isShow);
    bool RemoveItem(int element,bool isShow);
    bool AddItem(int element,bool isShow);
    bool GetItem(int place,bool isShow);
    void Print();
};

//the init function
CSet::CSet(int cap=100){///the defalt  capacity
    storage=new int[cap];
    capacity=cap;
    next=0;
}

//the adding capacity function
bool CSet::AddCap(int add=50,bool isShow=YES){//the default addition
    int newCapacity=capacity+add;
    int* newStorage=new int[newCapacity];
    for(int i=0;i<next;i++){
        newStorage[i]=storage[i];
    }
    delete[] storage;
    storage=newStorage;
    capacity=newCapacity;
    if(isShow==YES){
        cout<<"done."<<endl;
    }
    return true;
}
//the deduction function
bool CSet::SubCap(int ded=50,bool isShow=YES){//the default deduction
   if(capacity-next<=ded){
        if(isShow==YES){
            cout<<"no enough place."<<endl;
        }
        return false;
   }
   else{
        int newCapacity=capacity-ded;
        int* newStorage=new int[newCapacity];
        for(int i=0;i<next;i++){
            newStorage[i]=storage[i];
        }
        delete[] storage;
        storage=newStorage;
        capacity=newCapacity;
        if(isShow==YES){
            cout<<"done."<<endl;
        }
        return true;
   }
}
//the function which judge if the element is in the set
bool CSet::IsExist(int element,bool isShow=YES){
    bool flag=false;//the found flag
    for(int i=0;flag==false&&i<next;i++){
        if(storage[i]==element){
            flag=true;
            if(isShow==YES){
                cout<<"find in NO."<<i+1<<endl;
            }
            return flag;
        }
    }
    if(isShow==YES){
        cout<<"404 not found :)"<<endl;
    }
    return flag;
}
//the function which judge if the two set is euqal
bool CSet::IsEqual(CSet os,bool isShow=YES){
    if(os.next!=next){
        if(isShow==YES){
            cout<<"not equal."<<endl;
        }
        return false;
    }
    else{
        int flag=true;//the equal flag;
        //use loop to found
       for(int i=0;i<next;i++){
            if(os.IsExist(storage[i],NO)==false){
                flag=false;
                if(isShow==YES){
                    cout<<"not equal."<<endl;
                }
                return flag;
            }
       }
       if(isShow==YES){
            cout<<"equal."<<endl;
       }
       return flag;
    }
}

//the function which add item
bool CSet::AddItem(int element,bool isShow=YES){
    if(IsExist(element,NO)==true){
        if(isShow==YES){
            cout<<"already in it."<<endl;
        }
        return false;
    }
    if(capacity<=next){
        AddCap(50,NO);
    }
    storage[next]=element;
    next++;
    if(isShow==YES){
        cout<<"done."<<endl;
    }
    return true;
}
//the function which remove item
bool CSet::RemoveItem(int element,bool isShow=YES){
    if(IsExist(element,NO)==false){
        if(isShow==YES){
            cout<<"not found."<<endl;
        }
        return false;
    }
    //set the pointer
    int place=0;
    for(int i=0;i<next;i++){
        if(storage[i]==element){
            place=i;
            break;        
        }
    }
    //delete
    for(int inter=place;inter<next-1;inter++){
        storage[inter]=storage[inter+1];
    }
    storage[next-1]={0};
    next--;
    if(capacity-next>50){
        SubCap(50,NO);
    }
    if(isShow==YES){
        cout<<"done."<<endl;
    }
    return true;
}
//the function which return the intersection
CSet CSet::Intersection(CSet os,bool isShow=YES){
    //first: make new array to store the data and sort
    int arr1[os.next]={0};
    for(int i=0;i<os.next;i++){
        arr1[i]=os.storage[i];
    }
    qsort(arr1,os.next,sizeof(int),compare);
    int arr2[next]={0};
    for(int i=0;i<next;i++){
        arr2[i]=storage[i];
    }
    qsort(arr2,next,sizeof(int),compare);
    //second:make a new set and find the intersection
    CSet newSet(os.next);
    int p1=0,p2=0,sum=0;
    while(p1<os.next&&p2<next){
        if(arr1[p1]==arr2[p2]){
            newSet.AddItem(arr1[p1],NO);
            p1++;
            sum++;
        }
        else if(arr1[p1]<arr2[p2]){
            p1++;
        }
        else if(arr1[p1]>arr2[p2]){
            p2++;
        }
   }
   //third:print the result
   if(isShow==YES){
        if(sum==0){
            cout<<"no intersection."<<endl;
        }
        else{
            cout<<"done."<<endl;
        }
   }
   return newSet;
}

//the function which get the union
CSet CSet::Union(CSet os,bool isShow=YES){
    CSet newSet(os.next+next);
    for(int i=0;i<os.next;i++){
        newSet.AddItem(os.storage[i],NO);
    }
    for(int i=0;i<next;i++){
        if(newSet.IsExist(storage[i],NO)==false){
            newSet.AddItem(storage[i],NO);
        }
    }
    qsort(newSet.storage,newSet.next,sizeof(int),compare);
    if(isShow==YES){
        cout<<"done."<<endl;
    }
    return newSet;
} 

//the function which get the element
bool CSet::GetItem(int place,bool isShow=YES){
      if(place<1||place>next){
        if(isShow==YES){
            cout<<"not found."<<endl;
        }
        return false;
      }
      else{
            if(isShow==YES){
                cout<<"the element is "<<storage[place-1]<<endl;
            }
            return true;
       }
       
}
//the function which print the set
void CSet::Print(){
    cout<<"the set is:";
    for(int i=0;i<next;i++){
        cout<<storage[i]<<" ";
    }
    cout<<endl;
    return;
}

int main(){
    CSet set(10);
    set.AddItem(1,NO);
    set.AddItem(2,NO);
    set.Print();
    CSet oset(10);
    oset.AddItem(2,NO);
    oset.AddItem(3,NO);
    oset.Print();
    CSet debug=set.Intersection(oset,YES);
    debug.Print();
    CSet rebug=set.Union(oset,YES);
    rebug.Print();
    set.IsEqual(oset,YES);
    set.IsExist(3,YES);
    set.RemoveItem(2,YES);
    return 0;
}