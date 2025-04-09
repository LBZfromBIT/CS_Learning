//基本思路：与第二题类似，依然是一个走图类的问题，那就继续bfs
//思路来自:https://blog.csdn.net/m0_74200772/article/details/132677648

#include <bits/stdc++.h>

#define max 1100

int n,m,k;//全局变量

typedef struct{//存点信息的结构体
	int x;
	int y;
	int time;
}point;
point start,end,now,next;

char map[max][max];//存图
bool visit[max][max];//记录是否访问过的bool数组

std::queue <point> q;//队列

const int change[2][4]={{-1,0,1,0},{0,1,0,-1}};//用来做的改变数组

int isOK(int x,int y){//此处判断函数有三种状态
	if(x<1||x>n||y<1||y>m){//出图，说明说明沿这个方向迈再大步子也不行
		return -1;
	}
	else if(visit[x][y]==true){//走过了，但可能沿着该方向迈大点步子还能走
		return 0;
	}
	else if(map[x][y]=='#'){//撞墙，说明沿这个方向迈再大步子也不行（防止直接跨栏）
		return -1;
	}
	else{
		return 1;
	}
}

int main(){
	//重置
	memset(map,0,sizeof(map));
	memset(visit,false,sizeof(visit));
	int ans=-1;//结果，默认置-1，即没跑进去
	//读数据
	scanf("%d %d %d\n",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%c",&map[i][j]);
		}
		getchar();
	}
	scanf("%d %d %d %d",&start.x,&start.y,&end.x,&end.y);
	start.time=0;
	//加一种可能，起点即终点
	if(start.x==end.x&&start.y==end.y){
		printf("0\n");
		return 0;
	}
	//开始bfs
	q.push(start);
	visit[start.x][start.y]=true;
	while(!q.empty()){
		now=q.front();
		q.pop();
		for(int i=0;i<4;i++){//先对方向进行更改
			for(int j=1;j<=k;j++){//再考虑一步走多大（不然就出现一步跨过障碍直达终点了）
				next.x=now.x+change[0][i]*j;
				next.y=now.y+change[1][i]*j;
				next.time=now.time+1;
				if(isOK(next.x,next.y)==1){//位置合法
					if(next.x==end.x&&next.y==end.y){//找到
						ans=next.time;
						printf("%d\n",ans);
						return 0;//多层循环，直接跳出
					}
					else{
						q.push(next);
						visit[next.x][next.y]=true;
					}
				}
				else if(isOK(next.x,next.y)==0){//位置走过
					continue;
				}
				else{//位置非法且得换方向
					break;
				}
			}	
		}
	}
	printf("-1\n");//别忘了，如果进不去输出-1
}