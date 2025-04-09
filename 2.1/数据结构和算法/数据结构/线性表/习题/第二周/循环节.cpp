#include <stdio.h>
#include <stdlib.h>
typedef struct node
{   int         data;
    struct node * next;
} NODE;

//函数声明
NODE * find( NODE * , int * );
void outputring( NODE * );
void change( int , int , NODE * );

//函数定义
void outputring( NODE * pring )
{	NODE * p;
	p = pring;
	if ( p == NULL )
		printf("NULL");
	else
		do	{	printf("%d", p->data);
			p = p->next;
		} while ( p != pring );
	printf("\n");
	return;
}

//直接开个全局变量：begin指针
NODE *begin=NULL;//begin指向开始循环的节点
void change( int n, int m, NODE * head )//构建循环链表的函数，与上一问一致
{ 
    int array[10000][2]={0};//记录[余数][整除部分]的数组  **tips:数组别开小了，不然会RE
	int number=0,place=0;//number记录储存的余数数量，place将定位到重复出现余数的位置
	n=n*10;//先把被除数乘10,开始计算
	NODE *tail=head;//尾结点指针先指向头节点
	while(n!=0){//除非n=0,即上一次运算整除了,否则循环下去
	    int rest=n%m;//当前余数
	    int full=n/m;//当前整除
	    bool found=false;//判断是否找到重复余数
	    for(int i=1;i<=number;i++){
	    	if(array[i][1]==rest&&array[i][2]==full){//出现了重复余数且整除部分一致,从此处开始循环
	    		place=i;
	    		found=true;
	    		break;
			}
		}
		if(found==false){//还没出现循环
			NODE *point=(NODE*)malloc(sizeof(NODE));//新节点
			point->data=full;
			point->next=NULL;
			tail->next=point;
			tail=tail->next;
			number++;//更新余数数组
			array[number][1]=rest;
			array[number][2]=full;
			n=rest*10;//更新被除数
			continue;
		}
		else{//从第place位开始循环
		    begin=head;//begin定位到开始循环的节点
		    for(int i=0;i<place;i++){
		    	begin=begin->next;
			}
			tail->next=begin;
			break;//别忘了退出
		}	
	}
}

NODE * find( NODE * head, int * n )
{
	int lenth=0;
	NODE *cur=begin;
	//这里由于是循环链表，无法通过判断是否置空而结束遍历；
	//因此仿照outpring函数进行改写
	if(cur!=NULL){
		do{
			lenth++;
			cur=cur->next;
		}while(cur!=begin);
	}
	*n=lenth;
	return begin;
}

int main()
{   int n, m;
	NODE * head, * pring;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;

	change( n, m, head );
	pring = find( head, &n );
	printf("ring=%d\n", n);
	outputring( pring );

	return 0;
}

