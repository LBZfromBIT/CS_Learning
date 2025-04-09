#include <bits/stdc++.h>
#define MAX_SIZE 101
//基本思路：DFS,一条路走到黑
int n,m;//n行m列
int solution=0;//定义可能出现的方案数

typedef struct{//存点的信息的结构体
	int x;
	int y;
}point;

int change[2][4]={{1,0,0,-1},
                  {0,1,-1,0}};//运动优先级：下，右，左，上

int map[MAX_SIZE][MAX_SIZE];//存图二维数组
bool visit[MAX_SIZE][MAX_SIZE];//储存访问信息的二维数组

std::vector <point>way;//储存路径；

bool isOK(int x,int y){//判断位置是否合法的函数
	if(x<1||x>n||y<1||y>m){//出界了
		return false;
	}
	else if(map[x][y]==1){//撞墙了
		return false;
	}
	else if(visit[x][y]==true){//走回头路了
		return false;
	}
	else{
		return true;
	}
}

void dfs(int row,int column){//dfs函数
	if(isOK(row,column)==false||solution!=0){//位置不合法或者已经有了方案，直接回头
		return;
	}
	else if(row==n&&column==m){//在结束点
		solution++;
		visit[row][column]=true;
		point end;
		end.x=row;
		end.y=column;
		way.push_back(end);
		return;
	}
	else{//在一般点
		visit[row][column]=true;//表计该点访问
		point tmp;
		tmp.x=row;
		tmp.y=column;
		way.push_back(tmp);//把该点先放进去
		for(int i=0;i<4;i++){
			dfs(row+change[0][i],column+change[1][i]);
		}
		//其子树上的所有点都走过了而没有可行的点,其状态重置
		if(solution==0){
			way.pop_back();
		    visit[row][column]=false;
		    return;
		}
		else{//其子树上有方案，直接返回
			return;
		}
	}
	
}

int main(){
	//进行数据初始化
	memset(map,-1,sizeof(map));
	memset(visit,false,sizeof(visit));
	way.clear();
	//录入地图
	scanf("%d %d",&n,&m);
	for(int row=1;row<=n;row++){
		for(int column=1;column<=m;column++){
			scanf("%d",&map[row][column]);
		}
	}
	//应考虑，如果结果为墙，则直接输出不可能，否则进行bfs
	if(map[n][m]==1||map[1][1]==1){
		printf("There is no solution!\n");
	}
	else{
		dfs(1,1);
		if(solution==0){
			printf("There is no solution!\n");
		}
		else{
			for(auto iter:way){
				printf("<%d,%d> ",iter.x,iter.y);
			}
			printf("\n");
		}
	}
}