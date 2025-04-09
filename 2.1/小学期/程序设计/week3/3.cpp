#include <bits/stdc++.h>
using namespace std;
//基本思路：通过dfs+递归来实现
typedef struct{
	int row;//旋转行
	int column;//旋转列
	int time;//次数
}revolt;//储存旋转位置和旋转次数的结构体

int shudo[20][20]={0};//储存数独内容的
int rowcheck[20][20]={0};//检查每行数字的出现情况
int columncheck[20][20]={0};//检查每列数字出现情况

int minrevolt=10086;//最小步数
vector<revolt> nowre;//储存当前旋转方案的动数组
vector<revolt> minre;//储存最小旋转方案的动数组

int num(char c){//字符转数字函数
	if(c=='A'){
		return 10;
	}
	else if(c=='B'){
		return 11;
	}
	else if(c=='C'){
		return 12;
	}
	else if(c=='D'){
		return 13;
	}
	else if(c=='E'){
		return 14;
	}
	else if(c=='F'){
		return 15;
	}
	else{
		return c-48;
	}
}
void turnaround(int x,int y){//逆时针旋转函数
    x=x*4;
    y=y*4;
    for(int i=0;i<2;i++){
    	for(int j=i;j<3-i;j++){
    		int temp=shudo[x+i][y+j];
    		shudo[x+i][y+j]=shudo[x+j][y+3-i];
    		shudo[x+j][y+3-i]=shudo[x+3-i][y+3-j];
    		shudo[x+3-i][y+3-j]=shudo[x+3-j][y+i];
    		shudo[x+3-j][y+i]=temp;
		}
	}
}

bool isOK(int x,int y){//判断是否合法
	x=x*4;
    y=y*4;
    for(int i=x;i<x+4;i++){
    	for(int j=y;j<y+4;j++){
    		int temp=shudo[i][j];
    		if(rowcheck[i][temp]!=0||columncheck[j][temp]!=0){
    			return false;
			}
		}
	}
	
	for(int i=x;i<x+4;i++){
		for(int j=y;j<y+4;j++){
			int temp=shudo[i][j];
			rowcheck[i][temp]=1;
			columncheck[j][temp]=1;
		}
	}
	return true;
}

void unrevolt(int x,int y){//撤销检查合法数组
	x=x*4;
	y=y*4;
	for(int i=x;i<x+4;i++){
		for(int j=y;j<y+4;j++){
			int temp=shudo[i][j];
			rowcheck[i][temp]=0;
			columncheck[j][temp]=0;
		}
	}
}

void dfs(int x,int y,int count){//dfs函数
	if(x==4){//在当前操作下遍历了所有小区域,到达了最底层
		if(count<minrevolt){
			minrevolt=count;
			minre=nowre;
		}
		return;
	}
	
	for(int op=0;op<4;op++){
		if(isOK(x,y)==false){//不合法就一直转
			turnaround(x,y);
			continue;
		}
		
		revolt a;
		a.row=x+1;
		a.column=y+1;
		a.time=op;
		nowre.push_back(a);
		
		if(y==3){//遍历完一行
			dfs(x+1,0,count+op);
		}
		else{
			dfs(x,y+1,count+op);
		}
		//别忘了撤销状态
		nowre.pop_back();
		unrevolt(x,y);
		turnaround(x,y);
	}
}

int main(){
	int T;
	scanf("%d\n",&T);
	for(int i=1;i<=T;i++){
		minrevolt=10086;
		nowre.clear();
		minre.clear();
		memset(rowcheck,0,sizeof(rowcheck));
		memset(columncheck,0,sizeof(columncheck));
		
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				char temp;
				scanf("%c",&temp);
				shudo[i][j]=num(temp);
			}
			getchar();
		}
		
		dfs(0,0,0);
		printf("%d\n",minrevolt);
		
		for(auto iter:minre){
			for(int i=1;i<=iter.time;i++){
				printf("%d %d\n",iter.row,iter.column);
			}
		}
	}
}