#include <stdio.h>
#include <stdlib.h>

//线性表的链式储存，即链表形式，通过将结点内容存储在不连续的存储单元，实现了内部结点删除和插入的快速操作
//需要辨析的是：头指针和头节点不同
//头指针是必须存在的，其一定指向链表的第一个结点（第一个有数据元素的结点或头结点），因此头指针一般作为链表的名字
//而头结点是可选的，如果存在，其数据域可以存储链表长度，指针域一定指向下一个结点（即第一个数据元素结点）的存储位置
//
//
//
//接下来先对该链表进行构造
typedef int ElmeType;//假设数据元素的类型为整型
typedef struct node{//结构体定义如下
	ElmeType data;//数据域
	struct node *next;//指针域
}Node;
typedef struct node* LinkList;//重命名链表的指针结构为LinkList


//接下来，单链表的读取(链表L中的第i位，数据元素储存到e)基本思路就是遍历
#define OK 1
#define ERROR 0
#define NULL 0
typedef int STATUS;
STATUS GetElme(LinkList L,int i,ElmeType *e){//L为头指针
	Node *p=L->next;//指针p指向头结点
	int j=0;//当前位置指示器
	for(;j<i && p!=NULL;j++){//遍历前i-1个结点（注意条件p!=NULL,用以防止线性表长度不够i）
		p=p->next;
	}
	if(j==i){//查找成功
                *e=p->data;
		return OK;
	}
	else{//查找失败
                return ERROR;
	}
}


//接下来，单链表的插入(在链表L的第i位插入数据e)(思路：先遍历到第i个位置，做断除外接工作)
STATUS ListInsert(LinkList L,int i,ElmeType e){
       int j=0;
       Node *p=L->next;
       for(;j<i && p!=NULL;j++){
	       p=p->next;
       }
       if(j==i){//查找成功
	       LinkList s=(LinkList)malloc(sizeof(Node));
	       s->data=e;
               s->next=p->next;//注意此处的顺序
	       p->next=s; 
	       return OK; 
       }
       else{
               return ERROR;
       }
}


//接下来，单链表的删除(单链表L的第i位结点删除，并将被删除的结点的数据域赋给e)
STATUS ElmeDelete(LinkList L,int i,ElmeType *e){
	int j=0;
	LinkList p=L->next;
	for(;j<i-1 && p!=NULL;j++){//注意此处，p停在第i个结点的前一位
		p=p->next;
	}
	LinkList q=p->next;//q指向被删除的第i个结点
	if(j==i-1 && q!=NULL){//防止p在链表尾
	        *e=q->data;
                p->next=q->next;
		free(q);//别忘了把删除的结点free掉
		return OK;
	}
	else{
		return ERROR;
	}
}


//接下来，创建一个有效长度为n（不包含头结点）的单链表:头插法
void HeadCreateList(LinkList L,int n){
	LinkList head=(LinkList)malloc(sizeof(Node));
	L->next=head;
	head->data=n;//head为头结点,其数据域记录有效长度
        head->next=NULL;

	for(int i=1;i<=n;i++){//头插法，新结点放在head结点和老结点之间
		LinkList p=(LinkList)malloc(sizeof(Node));
		scanf("%d",&(p->data));
		p->next=head->next;
		head->next=p;
                
	}
}

//尾插法:新结点总跟在老结点之后，作为最后一个结点
void TailCreateList(LinkList L,int n){
	LinkList head=(LinkList)malloc(sizeof(Node));
	head->data=n;
	head->next=NULL;
	L->next=head;
	LinkList tail=head->next;//tail指针指向该链表的尾，方便尾插
	for(int i=1;i<=n;i++){
                LinkList p=(LinkList)malloc(sizeof(Node));
		scanf("%d",&(p->data));
		p->next=NULL;
		tail->next=p;//注意此处顺序，使tail直指向链表的尾
	        tail=tail->next;	
	}
}

//接下来，删除整个链表(思路：循环遍历，删除每个结点)
STATUS ClearList(LinkList L){
	LinkList p=L->next;//p指针指向当前结点，q结点指向p的下一结点，pq交替实现移动p指针
	while(p!=NULL){
		LinkList q=p->next;
		free(p);
                p=q;
	}
        L->next=NULL;//头指针置空
        return OK;
}

