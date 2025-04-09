#include <bits/stdc++.h>


/*
基本思路：
区间DP
使用time数组记录最小乘法次数
使用place数组记录最佳分割位置
*/

//全局变量区
#define M 105//最大元素数量
int store[M]={0};//储存阶数
int tt[M][M];//DP数组
int place[M][M];//截断位置

//全局函数
void lout(int s,int e){//递归输出结果函数
    if(s==e){//递归到底，相等
    	printf("A%d",s);
	}
	else{//不然，分治的递归输出最佳分段点前后两段
		printf("(");
		lout(s,place[s][e]);
		lout(place[s][e]+1,e);
		printf(")");
	}
	return;//别忘了return
}

int main(){//主函数
	int n=0;
	scanf("%d",&n);
	for(int i=0;i<=n;i++){
	//矩阵Ai的行数store[i-1],列数store[i]
	    scanf("%d",&store[i]);	
	}
	memset(tt,-1,sizeof(tt));//重置time数组
	memset(place,-1,sizeof(place));//重置place数组
	//开始DP
	for(int i=1;i<=n;i++){//第0行和第0列不用
		tt[i][i]=0;//自身不乘自身
	}
	//由于问题的特殊性，因此按矩阵列的长度来进行
	for(int lenth=2;lenth<=n;lenth++){//按长度
		for(int s=1;s<=n-lenth+1;s++){//起点位置
			int e=s+lenth-1;//终点位置
			int final=INT_MAX;//最终结果
			int pp=s;//断点位置
			for(int i=s;i<e;i++){
				int res=tt[s][i]+tt[i+1][e]+store[s-1]*store[i]*store[e];
				if(res<final){
					pp=i;//断点更新
					final=res;//结果更新
				}
			}
			tt[s][e]=final;
			place[s][e]=pp;
		}
	}
	printf("%d\n",tt[1][n]);
	if(n>1){
		lout(1,n);
	    printf("\n");
	}
	else{
		printf("(A1)\n");
	}
}