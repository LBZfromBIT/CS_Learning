#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//全局变量域
typedef int Status;
#define OK 1
#define ERROR 0;
typedef int Element_type;
#define basic 100;
#define add 50;

//数据结构域
typedef struct{
	Element_type *array;//数组
	int size;//空间大小
	int front;//队首指针(指队首）
	int tail;//队尾指针（指队尾空位）
	int block;//屏障指针，总在front之前
}Queue;

Queue L;

//基本操作域

/*
循环队列，我们规定浪费一个存储空间。即对于长度为5的指针，我们最多可以插入4个元素。

队列判空：循环队列，队首指针=队尾指针；

队列满：循环队列，队尾指针=屏障指针；(因此浪费一个空间）
*/


/*构建*/
Status init(Queue L){
	L.size=basic;
	L.number=0;
	L.array=(Element_type*)malloc(baisc*sizeof(Element_type));
	if(L.array==NULL){
		printf("ERROR\n");
		return ERROR;
	}
	L.front=0;
	L.tail=0;
	L.block=-1;
	return OK;
}

/*空否*/
Status empty(Queue L){
	if(L.front==L.tail){
		printf("YES\n");
		return OK;
	}
	else{
		printf("NO\n");
		return ERROR:
	}
}

/*满否*/
Status full(Queue L){
	if((L.tail==L.block){//循环起来
		printf("Yes\n");
		return OK;
	}
	else{
		printf("NO\n");
		return ERROR;
	}
	
}

/*加空间*/
Status expand(Queue L){
	if(L.array==NULL){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		Element_type *newarray=(Element_type*)malloc((L.size+add)*sizeof(Element_type));
		if(newarray==NULL){
			printf("ERROR\n");
			return ERROR;
		}
		else{
			L.size+=add;
			L.block=0;//屏障更新
			int place=1;//传递数据
			for(int i=0;L.front+i<tail;i++){
				newarray[place]=L.array[L.front+i];
				place++;
			}
			L.tail=place;
			L.front=1;
			old=L.array;
			L.array=newarray;
			free(old);
			return OK;
		}
	}
}

/*清空*/
Status clear(Queue L){
	if(L.array==NULL){
		printf("Not Found\n");
		return ERROR:
	}
	else{
		memset(L.array,0,sizeof(L.array));
		L.front=0;
		L.tail=0;
		L.block=-1;
		return OK;
	}
}

/*删除*/
Status Delete(Queue L){
	if(L.array==NULL){
		printf("Not Found\n");
		return ERROR:
	}
	else{
		free(L.array);
		L.front=0;
		L.tail=0;
		L.size=0;
		L.block=-1;
		return OK;
	}
}

/*入队*/
Status push(Queue L,Element_type e){
	if(L.array==NULL||full(L)==OK){
		printf("ERROR\n");
		return ERROR;
	}
	else{
		L.array[tail]=e;
		L.tail=(L.tail+1)%L.size;
		return OK;
	}
}

/*出队*/
Status pop(Queue L,Element_type *e){
	if(L.array==NULL||L.front==L.tail){
		printf("ERROR\n");
		return ERROR;
	}
	else{
		*e=L.array[front];
		L.front=(L.front+1)%L.size;
		L.block=(L.block+1)%L.size;
		return OK;
	}
}

/*获得队首*/
Status getfront(Queue L,Element_type *e){
	if(L.array==NULL||L.front==L.tail){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		*e=L.array[front];
		return OK;
	}
}

/*获得队尾*/
Status gettail(Queue L,Element_type *e){
	if(L.array==NULL||L.front==L.tail){
		printf("Not Found\n");
		return ERROR;
	}
	else{
		*e=L.array[tail-1];
		return OK;
	}
}
