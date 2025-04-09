//初始化，调库，定义常量参数
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int ElemType;//定义栈内元素类型
typedef int Status;//届时返回状态

#define OK 1;
#define ERROR 0;
#define BASIC_SIZE 100;
#define ADD_SIZE 50;

//定义一个栈结构体
typedef struct{
	ElemType *array;//栈的指针，指向该栈（数组）的第一个元素
	int top;//指向栈顶，由于连续储存，直接通过指针加数字访问栈顶
	int number;//储存当前进栈的元素数量
	int max;//储存栈内最多储存的元素数量，用来判断栈内空间是否足够
}stack;
stack *L;//示例栈

//1.建立一个栈的结构
Status create(stack *L){
	L->array=(stack*)malloc(BASIC_SIZE*sizeof(ElemType));//为栈内数组开空间
	if(L->array==NULL){//分配失败
		printf("内存储存失败\n");
		return ERROR;
	}
	else{
		memset(L->array,0,sizeof(L->array));//将栈内数组重置
		L->max=BASIC_SIZE;//最大空间BASIC_SIZE(后期可通过realloc再开空间）
		L->number=0;//此时空间内没有元素
		L->top=0;//栈顶无元素
		printf("初始化完成\n");
		return OK;
	}
}

//2.检查栈是否为空,空返回OK,非空或错误返回ERROR
Status empty(stack *L){
	if(L==NULL||L->array==NULL){
		printf("栈不存在\n");
		return ERROR;
	}
	if(L->number==0){
		printf("栈已空\n");
		return OK;
	}
	else{
		printf("栈非空\n");
		return ERROR;
	}
}

//3.清空一个栈但不删除
Status clear(stack *L){
	if(L==NULL||L->array==NULL){
		peintf("栈不存在\n");
		return ERROR;
	}
	else{
		memset(L->array,0,sizeof(L->array));//重置数组
		L->number=0;//计数器归零
		L->top=0;//栈顶标识归零
		return OK;
	}
	
}

//4.删除一个栈
Status free_stack(stack *L){
	if(L==NULL||L->array==NULL){
		printf("栈不存在\n");
		return ERROR;
	}
	else{
		free(L->array);//释放空间
		L->max=-1;//最大空间置-1
		L->number=-1;//计数器置-1
		L->top=-1;//栈顶标识置-1
		return OK;
	}
}

//5.压栈
Status push(stack *L,ElemType e){
	//先看有没有空间
	if(number==max){//空间满
		ElemType *newone=(stack*)realloc(L->array,(L->max+ADD_SIZE)*sizeof(ElmeType));//开新栈
		if(newone==NULL){
			printf("扩栈失败\n");
			return ERROR;
		}
		else{
			stack *old=L->array;//把旧的地址留存
			L->array=newone;//将新栈的地址挂载
			free(old);//释放旧的
			L->max=L->max+ADD_SIZE;//更新最大空间
		}
	}
	L->array[top+1]=e;//数据进栈
	L->number++;//计数器加1
	L->top++;//栈顶标识加一
	return OK;
}

//6.弹出栈顶,元素值存在e里
Status pop(stack *L,ElmeType *e){
	//先看是否为空
	if(L->number==0){
		printf("栈内无元素\n");
		return ERROR;
	}
	else{
		*e=L->array[top];//留存数据
		L->array[top]=0;//位置清空
		L->number--;//计数器减1
		L->top--;//栈顶标识减1
		return OK;
	}
}

//7.获得栈顶元素但不弹出,存在e里
Status gettop(stack *L,ElmeType *e){
	//先看是否为空
	if(L->number==0){
		printf("栈内无元素\n");
		return ERROR;
	}
	else{
		*e=L->array[top];//留存数据
		return OK;
	}
}