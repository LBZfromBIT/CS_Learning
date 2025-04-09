#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//基本思路：本质上还是一个01背包问题，但对方案加多了一个限制（超过成熟度）
typedef struct{//储存瓜信息的结构体
	int weigh;
	int full;
	int value;
}melon;
typedef long long int ll;
melon arr[110];//结构体数组,存瓜
ll dp[550][550];//动态规划表格，dp[j][k]表示在重量为j，成熟度为k时，该状态对应的最大价值

ll max (ll a,ll b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}
ll min (ll a,ll b){
	if(a<b){
		return a;
	}
	else {
		return b;
	}
}
int main(){
	memset(arr,0,sizeof(arr));
	memset(dp,-1,sizeof(dp));//默认价值置-1
	int n,time;
	scanf("%d %d",&n,&time);
	for(int i=1;i<=n;i++){
		scanf("%d %d %d",&(arr[i].weigh),&(arr[i].full),&(arr[i].value));
	}
	dp[0][0]=0;//一个瓜都没买，价值为0
	for(int i=1;i<=n;i++){//最外层，对每个瓜
		for(int j=500;j>=0;j--){//第二层，对当前可能的重量剩余
			for(int k=500;k>=0;k--){//最里层，对当前的成熟度
				if(dp[j][k]!=-1){//当前状态下有价值,加瓜有意义
					if(j+arr[i].weigh<500){//不超重
						dp[j+arr[i].weigh][min(k+arr[i].full,500)]=max(dp[j][k]+arr[i].value,dp[j+arr[i].weigh][min(k+arr[i].full,500)]);//最大值在（[j][k]状态最大+新瓜）和（原来新状态下最大值）之间选择
					}
				}
			}
		}
	}
	
	for(int i=0;i<time;i++){
		int W,V;
		scanf("%d %d",&W,&V);
		ll ans=-1;
		for(int j=0;j<=W;j++){
			for(int k=V;k<=500;k++){
				if(dp[j][k]>ans){
					ans=dp[j][k];
				}
			}
		}
		
		printf("%lld\n",ans);
	}
	
}