#include <bits/stdc++.h>
using namespace std;

/*基本思路：
DP进行处理，cost[][]存价格，Min存结果
解的形式：设状态Min(i,j)表示从i到j的最小花费，
解为Min(1,n)
状态转移函数：
Min(i,j)= 
         1)0,i==j
         2)min(cost(i,k)+Min(k,j)),其中i<k<=j
         
*/

//全局变量域
#define M 205//数组的最大范围
int cost[M][M]={0};
int Min[M][M]={0};

//全局函数域
int main(){
	int num=0;
	scanf("%d",&num);
	for(int row=1;row<=num;row++){
		for(int col=1;col<=num;col++){
			if(col<row){//禁止逆行
				cost[row][col]=INT_MAX;
			}
			else if(col==row){//原地转圈
				cost[row][col]=0;
			}
			else{
				scanf("%d",&cost[row][col]);
			}
		}
	}
	//开始DP
	for(int i=num;i>0;i--){
		for(int j=1;j<=num;j++){
			if(j<i){
				Min[i][j]=INT_MAX;
			}
			else if(j==i){
				Min[i][j]=0;
			}
			else{//j>i
				int ans=INT_MAX;
				for(int k=i+1;k<=j;k++){
					ans=min(ans,cost[i][k]+Min[k][j]);
				}
				Min[i][j]=ans;
			}
		}
	}
	printf("%d\n",Min[1][num]);
}