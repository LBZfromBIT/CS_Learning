//初始化，调用库，设置常量变量
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OK 1
#define ERROR 0

typedef int ElemType;//设元素类型为int
typedef int Status;//状态量

typedef struct NODE{//链表中储存数据元素的结点
	ElmeType inform;//数据元素自身
	struct NODE *next;//指向下一元素的指针
}node;

typedef struct{//栈的结构体，包含栈链表（栈顶总位于头结点之后）和计数器（无需考虑空间）
	node *array;//栈的链表
	int number;//计数器
}stack;

stack *L;//示例栈

//1.建立一个空栈
Status create(stack *L){
	L->array=(node*)malloc(sizeof(node));//L->array即为头结点
	if(L->array==NULL){
		printf("内存分配失败\n");
		return ERROR;
	}
	else{
		L->array->next=NULL;//头结点后先置空
	    L->array->inform=-1;//头结点数据元素置-1
	    L->number=0;//计数器置0
	    return OK:
	}
}

//2.检查栈是否为空，空则返回OK
Status empty(stack *L){
	if(L==NULL||L->number==-1){
		printf("栈不存在\n");
		return ERROR;
	}
	if(L->number==0){//检查计数器是否为0
		return OK;
	}
	else{
		return ERROR;
	}
}

//3.清空一个链表（只剩头结点，头结点初始信息不改变）
Status clear(stack *L){
	if(L==NULL||L->number==-1){
		printf("栈不存在\n");
		return ERROR;
	}
	while(L->number!=0){//栈内还有元素时
		node *top=L->array->next;//top指针指向栈顶
		L->array->next=top->next;//将栈顶下一个元素移到栈顶
		free(top);//释放原栈顶
		L->number--;//计数器减1
	}
	return OK;
}

//4.删除一个栈（连头结点也不剩了）
Status free_stack(stack *L){
	if(L==NULL||L->number==-1){
		printf("栈不存在\n");
		return ERROR;
	}
	else{
		while(L->number!=0){
			node *top=L->array->next;//指向栈顶
			L->array->next=top->next;//下一元素移动到栈顶
			free(top);
			L->number--;//计数器减1
		}
		L->number=-1;//计数器置-1,为栈被删除的标识
		return OK;
	}
}

//5.压栈
Status push(stack *L,ElemType e){
	if(L==NULL){
		printf("栈不存在\n");
		return ERROR:
	}
	else{
		node *newone=(node*)malloc(sizeof(node));//新结点
		if(newone==NULL){
			printf("空间分配失败\n");
			return ERROR;
		}
		newone->inform=e;//存入信息
		newone->next=L->array->next;//将原栈顶放在新的结点之后
		L->array->next=newone;//新结点作为栈顶放在头结点之后
		L->number++;//计数器加1
		return OK;
	}
}

//6.弹出栈顶
Status pop(stack *L,ElemType *e){
	if(L==NULL||L->number==-1){
		printf("栈不存在\n");
		return ERROR;
	}
	else if(L->number==0){
		printf("栈为空栈\n");
		return ERROR;
	}
	else{
		node *top=L->array->next;//指向栈顶
		*e=top->inform;//存信息
		L->array->next=top->next;//摘除栈顶
		free(top);//释放栈顶
		L->number--;//计数器减1
		return OK;
	}
}

//7.获得栈顶元素
Status getpop(stack *L,ElemType *e){
	if(L==NULL|L->number==-1){
		printf("栈不存在\n");
		return ERROR;
	}
	else if(L->number==0){
		printf("栈为空栈\n");
		return ERROR;
	}
	else{
		node *top=L->array->next;//栈顶指针
		*e=top->inform;//获取元素
		return OK;
	}
}