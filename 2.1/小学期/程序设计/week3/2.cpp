//新版本基础思路：https://blog.csdn.net/weixin_50295745/article/details/120271028
//基础在于：队列+bfs；

#include <bits/stdc++.h>
using namespace std;


char mp[110][110];//存图二维数组
bool visit[110][110][60];//储存某节点在某时刻是否访问过，第三维用于防止在一个怪的刷新周期里走过
int n,m,k;//基本信息

typedef struct{//储存点的信息的结构体
	int x;
	int y;
	int time;
}place;

place starting,ending,nowone,nextone;//开始点，结束点，当前点，下一点；


const int change[2][4]={{-1,0,1,0},
                        {0,1,0,-1}};


bool isOK(int x,int y,int time){//判断位置合法性函数
	if(x<1||x>n||y<1||y>m){//出界
		return false;
	}
	else if(mp[x][y]=='#'){//撞墙
		return false;
	}
	else if(mp[x][y]=='*'&&time%k!=0){//撞怪
		return false;
	}
	else if(visit[x][y][time%k]==true){//在一个刷新周期里走过了
	    return false;
	}
	else{
		return true;
	}
}

int main(){
	int group;
	scanf("%d",&group);
	while(group>0){
		//第一步，录入信息
		memset(mp,0,sizeof(mp));
		memset(visit,false,sizeof(visit));
		queue <place> q;//队列
		int ans=-1;//最终答案，默认状态下最大
		scanf("%d %d %d",&n,&m,&k);
		getchar();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%c",&mp[i][j]);
				if(mp[i][j]=='S'){
					starting.x=i;
					starting.y=j;
					starting.time=0;
				}
				else if(mp[i][j]=='E'){
					ending.x=i;
					ending.y=j;
				}
			}
			getchar();//每行结束有个换行
		}
		
		//开始处理数据（bfs）
		//先放起点进去
		q.push(starting);
		visit[starting.x][starting.y][starting.time%k]=true;
		//再进行bfs进队
		while(!q.empty()){
			nowone=q.front();//先把队首点取出为当前点
			q.pop();
			if(nowone.x==ending.x&&nowone.y==ending.y){//当前点即为结束点
	            ans=nowone.time;
	            break; 
			}
			else{//若非结束点，开始向四个方向取子点
				for(int i=0;i<4;i++){
					nextone.x=nowone.x+change[0][i];
					nextone.y=nowone.y+change[1][i];
					nextone.time=nowone.time+1;
					if(isOK(nextone.x,nextone.y,nextone.time)==false){
						continue;
					}
					else{
						q.push(nextone);
						visit[nextone.x][nextone.y][nextone.time%k]=true;
					}
				}
			}
		}
	    printf("%d\n",ans);
	    group--;
	}
}
