#include <bits/stdc++.h>
/*基本思路：
  最短路径问题，本题可以直接使用迪杰斯特拉算法求解
  具体思路参考：https://zhuanlan.zhihu.com/p/338414118
  本题中，无负权值，因此用-1代替无边
*/

//全局变量域
int road[1000][1000];//储存弧的邻接矩阵
int result[1000];//储存最终结果的数组
bool visit[1000];



//全局函数域

//在字母和数字间切换
int CtN(char a){
	return a-'a';
}

char NtC(int a){
	return a+'a';
}

int getmin(int pnum,int& place){
	int mindis=10086;
	for(int i=0;i<pnum;i++){
		if(result[i]!=-1&&visit[i]!=true&&result[i]<mindis){
			mindis=result[i];
			place=i;
		}
	}
	return mindis;
}

//迪杰斯特拉算法
void Dij(int pnum,char start){
	int begin=CtN(start);
	//初始化
	for(int i=0;i<pnum;i++){
		result[i]=road[begin][i];
	}
	result[begin]=0;
	visit[begin]=true;
    //逐个遍历，获得还未求得最小的最小点
    while(true){
    	int mp;//最小点位
    	int md=getmin(pnum,mp);//最小距离
    	if(md==10086){//遍历完成
    		break;
		}
		else{//遍历未结束
			visit[mp]=true;//该点确定
			for(int j=0;j<pnum;j++){
				if(visit[j]==true){
					continue;
				}
				else{//更新其他点距离
					if(road[mp][j]==-1){
						continue;
					}
					else{
						int pot=md+road[mp][j];
						if(pot<result[j]||result[j]==-1){
							result[j]=pot;
						}
						else{
							continue;
						}
					}
				}
			}
		}
	}
   return; 
	
}


int main(){
	int pnum,dnum;
	char start;
	memset(road,-1,sizeof(road));
	memset(result,-1,sizeof(result));
	memset(visit,false,sizeof(visit));
	scanf("%d,%d,%c",&pnum,&dnum,&start);
	getchar();
	for(int i=0;i<dnum;i++){
		char s,e;
		int dis;
		scanf("<%c,%c,%d>",&s,&e,&dis);
		getchar();
		road[CtN(s)][CtN(e)]=dis;
	}
	Dij(pnum,start);//使用迪杰斯特拉算法
	for(int i=0;i<pnum;i++){
		printf("%c:%d\n",NtC(i),result[i]);
	}
	return 0;
}
