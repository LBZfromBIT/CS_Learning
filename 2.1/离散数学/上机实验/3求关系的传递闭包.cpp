#include <bits/stdc++.h>

/*思路：
使用矩阵储存关系R的关系矩阵M
然后采用washell算法：
|->观察每一列，第i列中为1的元素<j,i>表示了可以从第j个点去到第i个点；
|  则我们将第j行的元素与第i行的元素进行逻辑加法，更新现在第j行的元素可以去到的点有哪些
|  更新了矩阵
|->重复，直到第n次矩阵更新完成
*/

//全局变量域
int M[12][12]={0};//基数不超过十二的矩阵
int array[200]={0};//用来前期存数
std::queue<int> ral;//用来记录出发点的队列
//全局函数域

//1.两行的逻辑加法
void logic_add(int ran,int back,int front){
	//ran为基数，back为结束点，front为出发点
	for(int i=0;i<ran;i++){
		if(M[front][i]==1||M[back][i]==1){//有1
			M[front][i]=1;
		}
		else{//无1
			M[front][i]=0;
		}
	}
	return;
}

//2.获得出发点函数
void get_point(int ran,int back){
	while(ral.empty()!=true){//重置
		ral.pop();
	}
	for(int i=0;i<ran;i++){
		if(M[i][back]==1){//找到
			ral.push(i);
		}
		else{
			continue;
		}
	}
	return;
}

int main(){
	int num=0,total=0;
	while(scanf("%d",&num)!=EOF){
		array[total]=num;
		total++;
	}
	int ran=(int)sqrt(total);//基数
	num=0;
	for(int i=0;i<ran;i++){//写入矩阵
		for(int j=0;j<ran;j++){
			M[i][j]=array[num];
			num++;
		}
	}
	//开始进行循环更新矩阵了
	for(int time=1;time<=ran;time++){
		for(int back=0;back<ran;back++){
			get_point(ran,back);
			while(ral.empty()!=true){//有出发点
				int front=ral.front();
				logic_add(ran,back,front);
				ral.pop();
			}
		}
	}
	//正常输出即可
	for(int row=0;row<ran;row++){
		for(int col=0;col<ran;col++){
			if(col!=ran-1){
				printf("%d ",M[row][col]);
			}
			else{
				printf("%d\n",M[row][col]);
			}
		}
	}
}