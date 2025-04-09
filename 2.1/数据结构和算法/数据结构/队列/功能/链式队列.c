#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//全局常量设置域
typedef int Element_type;
typedef int Status;
#define OK 1
#define ERROR 0


//数据结构设置域
/*结点结构*/
typedef struct NODE{
	Element_type info;//储存单元
	struct NODE *next;//下一个指针
}node;

/*队列结构*/
typedef struct{
	node *head;//队列的头结点
	node *front;//队首指针
	node *tail;//队尾指针
	int number;//计数
}Queue;
Queue L;

//基本操作部分
/*构建*/
Status init(Queue L){
	L.number=0;//数据置零
	L.head=(node*)malloc(sizeeof(node));//头结点挂载
	if(L.head==NULL){
		printf("ERROR!\n");
		return ERROR;
	}
	L.head->next=NULL;//尾巴置空
	L.front=NULL;//队首置空
	L.tail=NULL;//队尾置空
	return OK;
}

/*空否*/
Status empty(Queue L){
	if(L.number==0){/*也可替换为L.head->next==NULL*/
		printf("空\n");
		return OK;
	}
	else{
		printf("否\n");
		return ERROR;
	}
}

/*清除*/
Status clear(Queue L){
	if(L.head==NULL){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		while(L.number!=0){
			node *p=L.front;//p为遍历指针
			L.front=L.front->next;//队首后移
			free(p);//释放空间
			L.number--;//数字更新
		}
		L.head->next=NULL;//头结点尾巴置空
		return OK;
	}
}

/*删除*/
Status Delete(Queue L){
	//先清除
	if(L.head==NULL){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		while(L.number!=0){
			node *p=L.front;
			L.front=L.front->next;
			free(p);//释放空间
			L.number--;//数字更新
		}
		free(L.head);//头结点释放
		return OK;
	}
}

/*队尾入队*/
Status push(Queue L,Element_type e){
	if(L.head==NULL){
		printf("Not Found\n");
	}
	else{
		L.number++;
		node *p=(node*)malloc(sizeof(node));
		p->info=e;
		p->next=NULL;
		if(L.tail==NULL){//空队时
			L.head->next=p;//挂载
			L.front=p;
			L.tail=p;
		}
		else{//队伍非空时
			L.tail->next=p;//挂载
			L.tail=p;//队尾后移
		}
		return OK;
	}
}

/*队首出队*/
Status pop(Queue L,Element_type *e){
	if(L.head==NULL||L.front==NULL){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		*e=L.front->info;
		node *p=L.front;
		L.front=L.front->next;//队首后移
		L.head->next=L.front;//与头挂载
		free(p);
		L.number--;
		if(L.number==0){//空了
			L.tail=NULL;
		}
		return OK;
	}
}

/*拿头元素*/
Status getfront(Queue L,Element_type *e){
	if(L.head==NULL||L.front==NULL){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		*e=L.front->info;
		return OK;
	}
}

/*拿尾元素*/
Status gettail(Queue L,Element_type *e){
	if(L.head==NULL||L.tail==NULL){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		*e=L.tail->info;
		return OK;
	}
}