#include <bits/stdc++.h>
using namespace std;
/*
基本思路：
使用着色法，BFS对整个图进行遍历
着色过程中，将颜色存在visit数组中：0,1为两种颜色，-1表示未访问
*/

//全局变量域
#define M 100
int data[M][M]={0};
int visit[M];
queue <int> team;//储存邻接点的队列

//全局函数域
bool BFS(int num){//bfs函数
    for(int point=0;point<num;point++){//从每个点开始进行BFS
        memset(visit,-1,sizeof(visit));//访问数组重置
        team.push(point);
        visit[point]=0;
        while(team.empty()!=true){//非空时
            int cur=team.front();
            int ccolor=visit[cur];
            for(int i=0;i<num;i++){
                if(data[cur][i]==0){
                    continue;
                }
                else{//有从cur到i的路径
                    if(visit[i]==-1){
                        visit[i]=1-ccolor;
                        team.push(i);
                    }
                    else{
                        if(visit[i]==ccolor){
                            return false;
                        }
                        else{
                            continue;
                        }
                    }
                }
            }
            team.pop();
        }
    }
    return true;
}

int main(){
    //信息录入
    int num=0;
    scanf("%d",&num);
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            scanf("%d",&data[i][j]);
        }
    }
    //BFS处理
    bool status=BFS(num);
    if(status==true){
        printf("yes\n");
    }
    else{
        printf("no\n");
    }
}
