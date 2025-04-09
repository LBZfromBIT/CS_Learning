#include <bits/stdc++.h>
using namespace std;
/*
基本思路：
1.使用washell算法构建可达矩阵
2.对可达矩阵进行判断
全为1，强连通图；p[i][j]+p[j][i]=1,单项连通图；否则为弱连通图
*/

//全局变量域
#define M 100
int data[M][M]={0};

//全局函数域
void Logicadd(int num,int add,int added){
    for(int i=0;i<num;i++){
        if(data[add][i]==1||data[added][i]==1){
            data[added][i]=1;
        }
        else{
            data[added][i]=0;
        }
    }
    return;
}

void washell(int num){//washell算法构建可达矩阵
    queue <int> back;
    for(int time=1;time<=num;time++){
        for(int col=0;col<num;col++){
            for(int row=0;row<num;row++){
                if(data[row][col]==1){
                   back.push(row);
                }
                else{
                    continue;
                }
            }
            while(back.empty()!=true){
            	int tp=back.front();
            	Logicadd(num,col,tp);
            	back.pop();
			}
        }
    }
    for(int i=0;i<num;i++){//认为自可达
        data[i][i]=1;
    }
    return;
}

int main(){
    int num;
    scanf("%d",&num);
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            scanf("%d",&data[i][j]);
        }
    }

    washell(num);
    bool str=true;
    bool bad=false;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(data[i][j]+data[j][i]==0){
                str=false;
                bad=true;
            }
            else if(data[i][j]+data[j][i]==1){
                str=false;
            }
        }
    }
    if(str==true){
        printf("A\n");
    }
    else{
        if(bad==true){
            printf("C\n");
        }
        else{
            printf("B\n");
        }
    }
}