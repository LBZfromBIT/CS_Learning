#include <bits/stdc++.h>
using namespace std;

/*基本思路：
动态规划，meo[][]为储存数组，Max[][]为DP解数组
问题的解形式：设状态为Max(i,j)表示从第i行第j列出发到底的最大值
              则Max(0,0)为解
状态转移函数：
        |—meo[i][j],最底层行
Max(i,j)=
        |—max(Max[i+1][j],Max[i+1][j+1])+meo[i][j],其他
        
*/

//全局变量域
#define M 105
int meo[M][M]={0};
int Max[M][M]={0};

//全局函数域
int main(){
	int row=0;
	scanf("%d",&row);
	for(int i=0;i<row;i++){
		for(int j=0;j<=i;j++){
			scanf("%d",&meo[i][j]);
		}
	}
	
	//开始dp,先写边界i=row-1;
	for(int i=0;i<row;i++){
		Max[row-1][i]=meo[row-1][i];
	}
	
	for(int i=row-2;i>=0;i--){//行
		for(int j=0;j<=i;j++){
			Max[i][j]=max(Max[i+1][j],Max[i+1][j+1])+meo[i][j];
		}
	}
	printf("%d\n",Max[0][0]);
}

        
