//基本思路：构建循环链表，头结点记录长度，通过循环到危险数字摘链表的方式实现出队
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int no;//记录序号
	struct node* next;//记录下一个位置
}array;

array* makelist(int n){//构建循环链表的函数
    array *head=(array*)malloc(sizeof(array));
	head->no=1;//指定头结点
	head->next=NULL;
	
	array *tail=head;//指向尾节点指针
	
	for(int i=2;i<=n;i++){//循环建立列表
		array *p=(array*)malloc(sizeof(array));
		p->no=i;
		if(i==n){
			p->next=head;//循环起来
		}
		else{
			p->next=NULL;
		}
		tail->next=p;//接上p
		tail=tail->next;//向后挪
	}
	
	return head;//返回头结点指针
}

int main(){
	int n,k,m;//n个人，从k位置开启，m是危险数字
	scanf("%d,%d,%d",&n,&k,&m);
	if(n<1||k<1||m<1){
		printf("n,m,k must bigger than 0.\n");
	}
	else if(n<k){
		printf("k should not bigger than n.\n");
	}
	else{//该构建链表了
		array *head=makelist(n);
		//先定位到第k个
		array *cur=head;//cur指针指向当前节点
		while(cur->no!=k-1){
			cur=cur->next;
		}
		//此时cur指向编号为k-1的人，开始报数  
        for(int time=1;time<=n;time++)  
        {  
            for(int temp=0;temp<m-1;temp++) cur=cur->next; //此时cur为报m-1的结点   
            array *out=cur->next; //标记要出列的结点（报m的结点）   
            cur->next=out->next; //跳过要出列的结点  
            printf("%d",out->no);  
            free(out);  
            if((time==n)||(time%10==0)) printf("\n");  
            else printf(" ");  
        }  
		return 0;
	}
}