//思路：大家都到最开始人最多的横排上（即移动到y的中位上），然后按照纵列位置派纵列（调节x）

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

long long int x[200000],y[200000];

int mcompare(const void *a,const void *b){
	return *(long long int*)a>*(long long int*)b?1:-1;
}
long long int zheng(long long int a){//取绝对值函数
	if(a<0){
		return -a;
	}
	else{
		return a;
	}
}

int main(){
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){//读入数据
		scanf("%lld %lld",&x[i],&y[i]);
	}
	long long int sum=0;
	//先对y快排
	qsort(y,n,sizeof(long long int),mcompare);
	long long int sy=y[n/2];//取中位数，即为最近
	for(int i=0;i<n;i++){
		sum+=zheng(y[i]-sy);
	}
	//再对x快排，保证每个人要么不动，要么往最近的x位置移动
	long long int mid[200000]={0};
	qsort(x,n,sizeof(long long int),mcompare);
	for(int i=0;i<n;i++){
		mid[i]=x[i]-i;
	}
	qsort(mid,n,sizeof(long long int),mcompare);
	long long int sx=mid[n/2];
	for(int i=0;i<n;i++){
		sum+=zheng(x[i]-i-sx);
	}
	printf("%lld\n",sum);
}