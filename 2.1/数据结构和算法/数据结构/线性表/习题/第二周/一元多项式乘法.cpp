#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int    coef, exp;//coef为系数，exp为指数
    struct node  *next;
} NODE;

//函数声明
void multiplication( NODE *, NODE * , NODE * );
void input( NODE * );
void output( NODE * );

//函数定义
void input( NODE * head )//输入函数
{   int flag, sign, sum, x;
	char c;

    NODE * p = head;

	while ( (c=getchar()) !='\n' )
	{
		if ( c == '<' )
	    {    sum = 0;//数的加和（char型输入，转int)
	         sign = 1;//数的符号（+为1，-为-1）
	         flag = 1;//表示是每对中的第几个数（系数为1，指数为2）
        }
		else if ( c =='-' )
             sign = -1;
		else if( c >='0'&& c <='9' )
		{    sum = sum*10 + c - '0';
        }
		else if ( c == ',' )
        {    if ( flag == 1 )
             {    x = sign * sum;
                  sum = 0;
                  flag = 2;
		          sign = 1;
             }
        }
		else if ( c == '>' )
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );
             p->next->coef = x;
             p->next->exp  = sign * sum;
             p = p->next;
             p->next = NULL;
             flag = 0;
        }
    }
}

void multiplication( NODE *head1, NODE *head2 , NODE *head3 )//运算函数
{
	//基本思路：op1指针遍历head1，op2遍历head2,tail指向head3尾结点，每次op1与每个op2相乘得到一个新节点
	//用该节点数据与head3内所有进行比较，遇到相等的就加里头然后释放，否则停在比他大的第一个之前，往该位置插入
	NODE *op1=head1->next;//第一个操作数
	NODE *op2=head2->next;//第二个操作数
	NODE *tail=head3;//第三表的尾结点
	head3->exp=-1;//先将head3的头结点指数信息重置
	head3->coef=0;
	int lenth=0;//记录长度
	while(op1!=NULL){//遍历每一个1操作数
	    //别忘了重置op2到第一个
	    NODE *op2=head2->next;
	    //由于处理过程中op2的指数是单调增的，因此新的result可能的部分一定在上一次之后
		NODE *last=head3;//上次插入的位置指针
		while(op2!=NULL){//遍历每一个2操作数
			NODE *result=(NODE*)malloc(sizeof(NODE));//新空间存结果
			result->coef=op1->coef*op2->coef;
			result->exp=op1->exp+op2->exp;
			result->next=NULL;
			if(result->coef==0){//系数为0，直接下一次
				op2=op2->next;
				continue;
			}
			//接下来开始考虑放进head3里
			NODE *cur=last;
			NODE *front=NULL;
			while(cur!=NULL&&(cur->exp)<(result->exp)){
				front=cur;
				cur=cur->next;
			}
			//此时cur停在不小于result指数的第一个节点或队尾，进行讨论
			if(cur==NULL){//停在tail之后了
				tail->next=result;
				result->next=NULL;
				tail=tail->next;
				last=tail;
				lenth++;
			}
			else if(cur->exp==result->exp){//指数相等,系数相加不进队
				cur->coef+=result->coef;
				free(result);
				//还得判断系数是否为0
				if(cur->coef==0){
					front->next=cur->next;
					//判断cur是否为队尾
					if(cur==tail){
						tail=front;
					}
					free(cur);
					lenth--;
				}
				last=front;
			}
			else{//插入点
				front->next=result;
				result->next=cur; 
				last=result; 
				lenth++;
			}
			op2=op2->next;//op2指向下一个;	
		}
		op1=op1->next;
	}
	if(lenth==0){
		NODE *basis=(NODE*)malloc(sizeof(NODE));
		basis->coef=0;
		basis->exp=0;
		basis->next=NULL;
		head3->next=basis;
	}
}

void output( NODE * head )//输出函数
{
    while ( head->next != NULL )
    {   head = head->next;
        printf("<%d,%d>,", head->coef, head->exp );
    }
    printf("\n");
}

int main()
{   NODE * head1, * head2, * head3;

    head1 = ( NODE * ) malloc( sizeof(NODE) );
    input( head1 );

    head2 = ( NODE * ) malloc( sizeof(NODE) );
    input( head2 );

    head3 = ( NODE * ) malloc( sizeof(NODE) );
    head3->next = NULL;
    multiplication( head1, head2, head3 );

	output( head3 );
	return 0;
}
