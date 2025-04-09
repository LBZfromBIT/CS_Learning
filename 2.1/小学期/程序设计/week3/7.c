#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//基本思路：实话实说，没太看懂，思路借助了https://blog.csdn.net/m0_70241024/article/details/126680209

typedef long long int ll;

int place[2023]={0};//记录底位置的数组
ll dp[2023][2023]={0};//dp[i][j]代表从底到高第i个木头，以j位置为底的可能方案数

int main(){
	int n;
	scanf("%d\n",&n);
	for(int i=0;i<=n;i++){
		scanf("%d",&place[i]);//记录所有底位置
	}
	//由于最底下箭头是确定为底为place[0],头为place[1]的，且方案唯一
	dp[1][place[0]]=1;//递归的最底层条件
	for(int i=2;i<=n;i++){//从第二根木头开始
		//对于第i根木头，它的底可能为place[0]~place[i-1],但其头一定是place[i]
		//故dp[i][j]显然为dp[i][place[0]~dp[i][place[i-1]]的方案之和
		for(int p=0;p<=i;p++){//遍历底的位置
			int j=place[p];//j为当前的底
			//接下来要根据题目限制进行判断了（也是我没搞懂的地方）
			if((j<place[i]&&j<place[i-1])||(j>place[i]&&j>place[i-1])){
				dp[i][j]=dp[i-1][j];
			}
			else if(j==place[i-1]){
				if(j<place[i]){
					for(int k=j+1;k<=n+1;k++){
						dp[i][j]+=dp[i-1][k];
					}
				}
				else{
					for(int k=1;k<=j-1;k++){
						dp[i][j]+=dp[i-1][k];
					}
				}
			}
			else{
				dp[i][j]=0;
			}
			dp[i][j]=dp[i][j]%2147483647;//数可能很大，先取模
		}
	}
	ll ans=0;//结果=dp[n][place[0]]~dp[n][place[n+1]]之和
	for(int i=1;i<=n+1;i++){
		ans=ans+dp[n][i];
		ans=ans%2147483647;
	}
	printf("%lld\n",ans);
}
