#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct node
{   ElemType    data;
    struct node * next;
} NODE;
typedef NODE * LinkList;

void output( LinkList );
void change( int, int, NODE * );
LinkList createList( ElemType );
void inverse( LinkList ); 

LinkList createList( ElemType finish )	//finish：数据结束标记 
{
    ElemType x;
    NODE *newNode; 
    LinkList first = new NODE;   // 建立头结点
    first->next = NULL;
    first->data = finish;
    cin >> x;	      			// 约定以finish结束连续输入
    while ( x != finish )
	{
        newNode = new NODE;      // 建立新结点
       	newNode->data = x;
       	newNode->next = first->next; // ①
      	first->next = newNode;       // ②
		cin >> x;
    }
    return first;
}
void inverse(LinkList head){//翻转函数
    int lenth=0;
    LinkList tail=head;//tail为队尾节点
    while(tail->next!=NULL){
    	tail=tail->next;
    	lenth++;
	}//将tail指向尾结点
	if(lenth==0){
		return;
	}
	else{
		LinkList cur=head->next;//当前待翻转节点
		LinkList front=head;//上一个
		LinkList back=cur->next;//下一个
        for(int time=1;time<=lenth;time++){
    	   if(time==1){
    	   	cur->next=NULL;//第一个节点指针置空
		   }
		   else{
		   	cur->next=front;//其余节点指针指向前一个
		   }
		   if(time!=lenth){//没到最后一个节点时
		   	front=cur;//前节点后移
		    cur=back;//当前节点后移
		    back=back->next;
		   }
	    }
	    head->next=tail;//直接将头结点指针域指向原来的尾结点
	    return;
	}
}

void output( LinkList head )
{   cout << "List:";
	while ( head->next != NULL )
	{   cout << head->next->data << ",";
		head = head->next;
	}
	cout << endl;
}

int main(int argc, char** argv) 
{
	LinkList head;

	head = createList( -1 );
	output( head );
	inverse( head );
	output( head );
	return 0;
}
