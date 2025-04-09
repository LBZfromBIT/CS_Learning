#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//基本思路：本质上是个很单纯的01背包问题，可以直接套模板来解决问题
//本题中：限制量为总时间n，共有m个物品，其价值可看为time*w;
//转移方程：f[i][j]=max(f[i-1][j],f[i-1][j-time]+time*w

int n,m;//时间总数n,题目数m

int f[26][30000];

typedef struct{
	int time;
	int worth;
}que;
que nare[26];

int max(int a,int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

int main(){
	scanf("%d %d\n",&n,&m);
	memset(f,0,sizeof(f));//初始化动态规划表格
	memset(nare,0,sizeof(nare));//初始化结构数组
	for(int i=1;i<=m;i++){//录入信息
		scanf("%d %d",&nare[i].time,&nare[i].worth);
	}
	//开始整动态规划
	for(int row=1;row<=m;row++){//横行表示当前考虑哪个物品(下标与结构数组对应）
		for(int column=1;column<=n;column++){//纵列表示还有多少空间余量
		    //如果当前空间还有余量能放进去当前物品
		    if(column>=nare[row].time){
		    	f[row][column]=max(f[row-1][column],f[row-1][column-nare[row].time]+nare[row].time*nare[row].worth);
			}
			else{//余量不足，只能不放
				f[row][column]=f[row-1][column];
			}
		}
	}
	printf("%d\n",f[m][n]);
}
