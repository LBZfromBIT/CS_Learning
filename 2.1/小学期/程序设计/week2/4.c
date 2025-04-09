#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//还是贪心算法+排序，只不过要考虑能否实现合成效果

typedef struct {//此处我们人为规定长>宽>高，方便我们后面有效合成
    int NO;
	long long int a;//长
	long long int b;//宽
	long long int c;//高
}cst;
cst stone[100000];//储存信息的数组

int lcmp(const void *a,const void *b){//实现降序的比较函数
	return *((long long int*)a)<*((long long int*)b)?1:-1;
}

void set(cst *p){//处理长宽高函数
	long long int array[3]={0};
	array[1]=p->a;
	array[2]=p->b;
	array[3]=p->c;
	qsort(&(array[1]),3,sizeof(long long int),lcmp);
	p->a=array[1];
	p->b=array[2];
	p->c=array[3];
	
}


int hcmp(const void* a,const void* b){//实现降序的比较函数
    cst *p=(cst*)a;
    cst *q=(cst*)b;
	if(p->a!=q->a){
		return (p->a)<(q->a)?1:-1;
	}
	else if(p->b!=q->b){
		return (p->b)<(q->b)?1:-1;
	}
	else{
		return (p->c)<(q->c)?1:-1;
	}
}

long long int min(long long int a,long long int b){
	if(a>b){
		return b;
	}
	else{
		return a;
	}
}

int main(){
	memset(stone,0,sizeof(stone));
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){//按长宽高实现数据录入
		scanf("%lld %lld %lld",&(stone[i].a),&(stone[i].b),&(stone[i].c));
		set(&(stone[i]));
		stone[i].NO=i;
	}
	//对于单水晶而言：由于水晶球直径是由立方体最短边决定，即高，因此遍历高度找最大即可
	long long int max=0;
	int chose=0,status=1;
	for(int i=1;i<=n;i++){
		if(stone[i].c>max){
			max=stone[i].c;
			chose=i;
		}
    }

	
	//现在考虑双水晶：由于水晶球直径由高决定，因此应当选择两个长宽一致的水晶合成增加高度
	//直接进行循环遍历匹配，其复杂度为o(n^2),我们不如先进行快速排序（以长宽高依次为权重）
	//这样使得我们每次查看是否匹配时，只需要比较相邻的两个就行了
	qsort(&stone[1],n,sizeof(cst),hcmp);
	for(int i=1;i<n;i++){
		if(stone[i].a==stone[i+1].a&&stone[i].b==stone[i+1].b){//可以合成
		    long long int newc=stone[i].c+stone[i+1].c;
			if(max<min(newc,stone[i].b)){//新的立方体直径由新的高和原宽较小值决定
				max=min(newc,stone[i].b);
				status=0;
				chose=i;
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        }
	}
	if(status){
		printf("1\n%d\n",chose);//由于后面排序时更改了数组顺序，单水晶情况下的chose没变，但stone[chose].NO变了
	}
	else{
		printf("2\n%d %d\n",stone[chose].NO,stone[chose+1].NO);
	}
	
}