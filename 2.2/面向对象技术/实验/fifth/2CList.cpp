#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

class CStudent
{
   private:
        string name;
        int age;
    public:
        CStudent();
        CStudent(string n,int a);
        string getname();
        int getage();
        CStudent& operator = (const CStudent& os);
        bool operator == (const CStudent& os);
};
//constructor
CStudent::CStudent(){
       name=" ";
       age=0;
}
CStudent::CStudent(string n,int a){
    name=n;
    age=a;
}
//return name
string CStudent::getname(){
    return name;
}
//return age
int CStudent::getage(){
    return age;
}
//overload operator
CStudent& CStudent::operator = (const CStudent& os){
    name=os.name;
    age=os.age;
    return *this;
}
//compare two student
bool CStudent::operator == (const CStudent& os){
    if(name==os.name&&age==os.age){
        return true;
    }
    else{
        return false;
    }
}

template <typename T> 
class CList
{
    private:
       //using node list to store data
        typedef struct Node{
            T body;//data body
            struct Node* next;//pointer
        }node;

        node* head;//head node pointer
        node* tail;//tail node pointer
        int num;//number of nodes
    public:
        CList();
        ~CList();
        void Add(const T& item);
        void Remove(int index);
        T& operator [](int index);
};
//init constructor
template <typename T>
CList<T>::CList(){
    head=new node;
    head->next=NULL;
    tail=head;
    num=0;
}
//destructor
template <typename T>
CList<T>::~CList(){
    while(num!=0){
        node *temp=head->next;
        head->next=temp->next;
        if(temp->next==nullptr){
            tail=head;//no node left
        }
        delete temp;
        num--;
    }
    delete head;
}
//add a node
template <typename T>
void CList<T>::Add(const T& item){
    node *temp=new node;
    temp->body=item;
    temp->next=nullptr;
    tail->next=temp;
    tail=temp;
    num++;
    return ;
}
//remove a node
template <typename T>
void CList<T>::Remove (int index){
    if(index<0||index>=num){
        cout<<"index out side."<<endl;
        return ;
    }
    else{
        node* iter=head->next;//to the 0 one
        node* before=head;
        for(int i=0;i<index;i++){
            before=iter;
            iter=iter->next;
        }
        before->next=iter->next;
        num--;
        if(iter->next==nullptr){//the last one
            tail=before;
        }        
        delete iter;
        return ;
    }
}
//return the node of index
template <typename T>
T& CList<T>::operator [] (int index){
    if(index<0||index>=num){
        cout<<"index out side."<<endl;
        return head->body;
    }
    else{
        node* iter=head->next;
        for(int i=0;i<index;i++){
            iter=iter->next;
        }
        return iter->body;
    }
}

int main(){
    CStudent s1("Joan", 22), s2("John", 19),s3("Joe", 22);
    CList<CStudent> listStudent;
    listStudent.Add(s1);
    listStudent.Add(s2);
    listStudent.Add(s3);
    listStudent.Remove(1); // 1 is the 2rd element index of listStudent
    if (listStudent[0] == listStudent[1]) // If two students have same age.
        cout << "Equal." << endl;
    else
        cout << "Not equal." << endl;
    return 0;
}