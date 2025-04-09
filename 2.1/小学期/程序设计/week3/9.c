#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 2020
//基本思路：一个变种的01背包问题
//先读入数据，拿到基数V，而普通背包问题的j（即背包余量）在本题中转化为了对V的余数（0~V-1）
//最终答案也就变成了dp[n][0]的数量再减一（减一是因为排除dp[0][0]=1这种物品为空的不可能方案
typedef long long int ll;
ll volumn[max]={0};//存提及的数组
ll dp[max][max]={0};//存方法数的二维数组

int main(){
	int n,V;//物品数量和体积基数
	scanf("%d %d",&n,&V);
	ll sum=0;
	for(int i=1;i<=n;i++){//读入信息
		scanf("%d",&volumn[i]);
	}
	dp[0][0]=1;//放0个物品，余量为空->唯一
	for(int row=1;row<=n;row++){//对物品遍历
		for(int column=0;column<V;column++){//对空间余量遍历
			dp[row][column]=dp[row-1][column];//不放入新物品的方案数更新
		}
		for(int column=0;column<V;column++){//对放入新物品的方案数更新(前一个done+往里放一个）
			dp[row][(column+volumn[row]%V)%V]=(dp[row-1][column]+dp[row][(column+volumn[row]%V)%V])%10000000;
		}
	}
	ll ans=(dp[n][0]-1)%10000000;//别忘了把(0，0)方案剪掉
	printf("%lld\n",ans);
}