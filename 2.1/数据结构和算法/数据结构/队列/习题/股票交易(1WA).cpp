#include <bits/stdc++.h>

/*
基本思路：
本质上就是三个函数
1.写入函数：
2.显示函数
3.删除函数
*/


//全局变量区
typedef struct paper{
	int uid;//委托id
	int id;//股票编码
	float price;//价格
	int quantity;//数量
	char type;//类型（b买s卖）
	struct paper *next;//指向下一个单子的指针
	
}spt;//委托单结构

typedef struct{
	spt *basic;//指向头结点
	spt *head;//指向队首
	spt *tail;//指向队尾
}queue;//队列结构

queue buy_team;//买家队列
queue sell_team;//卖家队列

//函数区
//0.1.取小值函数
int getmin(int a,int b){
	if(a<b){
		return a;
	}
	else{
		return b;
	}
}
//0.2初始化队列
void init(queue *a){
	spt *node=(spt*)malloc(sizeof(spt));
	node->next=NULL;
	a->basic=node;
	a->head=NULL;
	a->tail=NULL;
}

//1.添加函数
void add(int uuid,int ustockid,float uprice,int uquantity,char utype){
	//1.建立结点
	spt *node=(spt*)malloc(sizeof(spt));
	node->uid=uuid;
	node->id=ustockid;
	node->price=uprice;
	node->quantity=uquantity;
	node->type=utype;
	node->next=NULL;
	//先看类型
	if(node->type=='b'){//买家单
		//在卖家队列里撮合(卖家价格低的先卖）
		spt *p=sell_team.head;
		spt *front=sell_team.basic;
		//先让p指向同股票id的卖家位置
		while(p!=NULL){
			if(p->id==node->id){
				break;
			}
			else{
				front=front->next;
				p=p->next;
			}
		}
		
		//在p指针非空时,开始循环匹配订单;p指针为空，意味着不存在可以成交的交易
		if(p!=NULL){
			while(p!=NULL&&(p->id)==(node->id)&&(p->price)<=(node->price)&&node->quantity!=0){
				float dealprize=(p->price+node->price)/2.0;//交易价格取平均
				int dealquantity=getmin(node->quantity,p->quantity);//交易量取小值
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",dealprize,dealquantity,node->uid,p->uid);
				node->quantity=node->quantity-dealquantity;//更新数量
				p->quantity=p->quantity-dealquantity;
				if(p->quantity==0){//该订单完成，删除订单
					spt *old=p;
					front->next=p->next;
					p=p->next;
					free(old);
					//更新队首队尾指针
					sell_team.head=sell_team.basic->next;
					if(p==NULL){
						sell_team.tail=front;
					}
				}
			}
		}
		//完成匹配，看买家是否还有余量
		if(node->quantity==0){//无余量，结束
			free(node);
			return;
		}
		else{//有余量，买家队列需按股票编号升序--价格降序--时间降序排列
			spt *place=buy_team.head;
			front=buy_team.basic;
			//先按编号升序
			while(place!=NULL){//place将停在不大于node的编码的位置(不一定等于）
				if(place->id<node->id){
					front=front->next;
					place=place->next;
				}
				else{
					break;
				}
			}
			//判断place的id与node是否一样
			while(place!=NULL&&place->id==node->id){//一致时，按价格降序--时间降序定位place；不一致时即可退出
				if(place->price>=node->price){
					front=front->next;
					place=place->next;
				}
				else{
					break;
				}
			}
			//然后在front和place间插入node
			front->next=node;
			node->next=place;
			//更新队首队尾
			buy_team.head=buy_team.basic->next;
			if(place==NULL){
				buy_team.tail=node;
			}
			return;
		}
	}
	else{//卖家单，
		//在买家队列里撮合(买家价格高的先买）
		spt *p=buy_team.head;
		spt *front=buy_team.basic;
		//先让p指向同股票id的卖家位置
		while(p!=NULL){
			if(p->id==node->id){
				break;
			}
			else{
				front=front->next;
				p=p->next;
			}
		}
		//在p指针非空时,开始循环匹配报价；p为空，无合理报价
		if(p!=NULL){
			while(p!=NULL&&(p->id)==(node->id)&&(p->price)>=(node->price)&&node->quantity!=0){
				float dealprize=(p->price+node->price)/2.0;//交易价格取平均
				int dealquantity=getmin(node->quantity,p->quantity);//交易量取小值
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",dealprize,dealquantity,node->uid,p->uid);
				node->quantity=node->quantity-dealquantity;//更新数量
				p->quantity=p->quantity-dealquantity;
				if(p->quantity==0){//该订单完成，删除订单
					spt *old=p;
					front->next=p->next;
					p=p->next;
					free(old);
					//更新队首队尾
					buy_team.head=buy_team.basic->next;
					if(p==NULL){
						buy_team.tail=front;
					}
				}
			}
		}
		//完成匹配，看卖家是否还有余量
		if(node->quantity==0){//无余量，结束
			free(node);
			return;
		}
		else{//有余量，卖家队列需按股票编号升序--价格升序--时间降序排列
			spt *place=sell_team.head;
			front=sell_team.basic;
			//先按编号升序定位
			while(place!=NULL){
				if(place->id<node->id){
					front=front->next;
					place=place->next;
				}
				else{
					break;
				}
			}
			//判断node的id与place是否一致
			while(place!=NULL&&place->id==node->id){//一致时在按价格升序,并按时间降序
				if(place->price<=node->price){
					front=front->next;
					place=place->next;
				}
				else{
					break;
				}
			}
			//然后在front和place间插入node
			front->next=node;
			node->next=place;
			//更新队首队尾
			sell_team.head=sell_team.basic->next;
			if(place==NULL){
				sell_team.tail=node;
			}
			return;
		}
	}
}

//2.显示函数
void view(int sid){
	//先显示buyorders
	printf("buy orders:\n");
	spt *p=buy_team.head;
	bool find=false;
	while(p!=NULL){
		if(p->id!=sid){
			if(find==false){
				p=p->next;
			}
			else{
				break;
			}	
		}
		else{
			find=true;
			printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",p->uid,p->id,p->price,p->quantity,p->type);
			p=p->next;
		}
	}
	
	//再显示sellorders
	printf("sell orders:\n");
	p=sell_team.head;
	find=false;
	while(p!=NULL){
		if(p->id!=sid){
			if(find==false){
				p=p->next;
			}
			else{
				break;
			}	
		}
		else{
			find=true;
			printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",p->uid,p->id,p->price,p->quantity,p->type);
			p=p->next;
		}
	}
	return ;
}

//3.删除函数
void Delete(int suid){
	bool find=false;
	//先从买家队列里找
	spt *p=buy_team.head;
	spt *front=buy_team.basic;
	while(p!=NULL){//定位到该订单
		if(p->uid!=suid){
			front=front->next;
			p=p->next;
		}
		else{
			find=true;
			printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",p->uid,p->id,p->price,p->quantity,p->type);
			//删除结点
			spt *old=p;
			front->next=p->next;
			p=p->next;
			free(old);
			//更新队首队尾
			if(p==NULL){
				buy_team.tail=front;
			}
			buy_team.head=buy_team.basic->next;
			break;
		}
	}
	if(find==true){
		return;
	}
	//再在卖家队里找
	p=sell_team.head;
	front=sell_team.basic;
	while(p!=NULL){
		if(p->uid!=suid){
			front=front->next;
			p=p->next;
		}
		else{
			find=true;
			printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",p->uid,p->id,p->price,p->quantity,p->type);
			//删除结点
			spt *old=p;
			front->next=p->next;
			p=p->next;
			free(old);
			//更新队首队尾
			if(p==NULL){
				sell_team.tail=front;
			}
			sell_team.head=sell_team.basic->next;
			break;
		}
	}
	if(find==true){
		return;
	}
	else{
		printf("not found\n");
		return;
	}
}

int main(){
	//初始化
	int op=-1;//操作
	int order=1;//记录uid
	init(&buy_team);//初始化
	init(&sell_team);
	
	//开始操作
	while(1){
		scanf("%d",&op);//录入操作
		
		if(op==1){
			//录入初始数据
			int id;
			float price;
			int quantity;
			char type;
			scanf("%d %f %d %c",&id,&price,&quantity,&type);
			
			//开始处理
			printf("orderid: %04d\n",order);
			add(order,id,price,quantity,type);
			order++;
		}
		
		else if(op==2){
			//录入初始数据
			int id;
			scanf("%d",&id);
			
			//开始处理
			view(id);
		}
		
		else if(op==3){
			//录入初始数据
			int uid;
			scanf("%d",&uid);
			
			//开始处理
			Delete(uid);
		}
		
		else if(op==0){
			break;
		}
	}	
	return 0;
}