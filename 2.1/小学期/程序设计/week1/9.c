#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//基本思路：本质上就是枚举，但暴力枚举肯定够呛了（即对每一个的灯的开关进行操作，看结果能否实现）
//但会有最多2^16种遍历情况，太吓人了

//进阶思路：来自：https://blog.csdn.net/weixin_43787043/article/details/108506008
//使用DFS算法，由于对于一个灯来说，按灯2次等于没摁，所以不会出现一个灯操作多次的可能；
//其次，按行来看，上一行的灯的亮暗将有他的下一行直接决定，因此我们可以按行来做，只遍历第一行
int n,m;
int table[20][20]={0};
int sci[20][20]={0};
void change(int *light){//换灯色操作
	if(*light==1){
		*light=0;
	}
	else{
		*light=1;
	}
}

void tap(int array[20][20],int row,int column){
	change(&(array[row][column]));
	if(row>1){
		change(&(array[row-1][column]));
	}
	if(row<n){
		change(&(array[row+1][column]));
	}
	if(column>1){
		change(&(array[row][column-1]));
	}
	if(column<m){
		change(&(array[row][column+1]));
	}
}

void copy(){//复制表格的函数
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sci[i][j]=table[i][j];
		}
	}
}

int result(){//在确定第一行状态后，检验整个表状态并计数
	int step=0;
	copy();
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			if(sci[i][j]==1){
				tap(sci,i+1,j);
				step++;
			}
		}
	}
	int status=1;
	for(int i=1;i<=m;i++){
		if(sci[n][i]==1){
			status=0;
			break;
		}
	}
	if(status){
		return step;
	}
	else{
		return -1;
	}
	
}

void find(int column,int temp,int *count){//进行dfs的核心：递归遍历
	if(column>m){//递归最底层条件：遍历完第一行
		int ans=result();
		if(ans==-1){
			return;
		}
		else{
			if(temp+ans<*count){
				*count=temp+ans;
				return;
			}
		}
	}
	else{
		tap(table,1,column);//改变当前位置灯的情况
		find(column+1,temp+1,count);
		tap(table,1,column);//不改变当前位置灯的情况
		find(column+1,temp,count);
	}
}



int main(){
	scanf("%d %d",&n,&m);//n行m列
	getchar();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char number;//由于是一行行输入，那就先用字符来，一个个转换
			scanf("%c",&number);
			table[i][j]=(int)number-48;
		}
		getchar();
	}
	int result=1024;
	find(1,0,&result);
	printf("%d\n",result);
}
