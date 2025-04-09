#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//version 1:暴力绘制图表（0空1水），遍历每行水的格数（会爆tle)
//
//version 2:我们沿用‘4.北理挖坑’的思路，将地面高度的数组拿到后，研究每个列的信息而非图表中每个点的信息
//           我们不难将湖比作一个盆，盆底凹凸不平但总向上突起，那么决定每一列存水量的关键，就在于这一列左侧和右侧最大高度的小值-该列地面的高度
//           答案不就出来了！！！
//version 3:出现TLE了，怀疑是主函数栈爆了，尝试着把高度数组拿出来
//version 4：还是TLE，v3代码的复杂度为O(n^2),在处理小数据下OK，大数据下还是会TLE；没办法，只能将遍历左右求最大的过程拿出来，进行预处理降低复杂度了


/*代码*/
long long int high[100000]={0};//地面高度数组
long long int before[100000]={0};//左侧最大高度
long long int next[100000]={0};//右侧最大高度
long long int min(long long int a,long long int b){
	if(a>=b){
		return b;
	}
	else{
		return a;
	}
}

int main(){
	int T;
	scanf("%d",&T);//测试组数
	for(int i=1;i<=T;i++){
		int wide=0;//湖的宽度，即数组上界
		scanf("%d",&wide);
		memset(high,0,sizeof(high));
		memset(before,0,sizeof(before));
		memset(next,0,sizeof(next));
		for(int j=1;j<=wide;j++){
			if(j!=wide){
				scanf("%lld ",&high[j]);
			}
			else{
				scanf("%lld",&high[j]);
			}
		}
		
		long long int bmax=0;//拿到记录每个列左侧最大数的数组
		before[1]=0;
		for(int i=2;i<=wide;i++){
			if(high[i-1]>bmax){
				bmax=high[i-1];
				before[i]=bmax;
			}
			else{
				before[i]=bmax;
			}
		}
		
		long long int nmax=0;//拿到记录每个列右侧最大数的数组
		next[wide]=0;
		for(int i=wide-1;i>=1;i--){
		    if(high[i+1]>nmax){
		    	nmax=high[i+1];
		    	next[i]=nmax;
			}
			else{
				next[i]=nmax;
			}		
		}

		long long int sum=0;//sum为总和
		for(int column=2;column<wide;column++){
			if(high[column]>=min(before[column],next[column])){
				continue;
			}
			else{
				sum=sum+min(before[column],next[column])-high[column];
			}
        }
		printf("%lld\n",sum);
	}
}
