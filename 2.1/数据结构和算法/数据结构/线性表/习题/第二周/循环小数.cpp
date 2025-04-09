#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int         data;
    struct node * next;
} NODE;

void output( NODE *, int );
void change( int, int, NODE * );

void output( NODE * head, int kk )//输出函数
{   int k=0;

	printf("0.");
	while ( head->next != NULL && k<kk )
	{   printf("%d", head->next->data );
		head = head->next;
		k ++;
	}
	printf("\n");
}

void change(int n,int m,NODE *head){
	//编写函数，关键在于找到循环的开头和结尾，思路：先将n*10然后除m，整除部分记录在节点中，余数部分也记录在数组当中，一旦余数出现重复，意味着开启了循环
	int array[10000][2]={0};//记录[余数][整除部分]的数组  **tips:数组别开小了，不然会RE
	int number=0,place=0;//number记录储存的余数数量，place将定位到重复出现余数的位置
	n=n*10;//先把被除数乘10,开始计算
	NODE *tail=head;//尾结点指针
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
		else{//从第i位开始循环
		    NODE *begin=head;//begin定位到开始循环的节点
		    for(int i=0;i<place;i++){
		    	begin=begin->next;
			}
			tail->next=begin;
			break;//别忘了退出
		}	
	}
}

int main()
{   int n, m,k;
	NODE * head;

	scanf("%d%d%d", &n, &m, &k);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;
	change( n, m, head );
	output( head,k );
	return 0;
}
