#include <bits/stdc++.h>
#define max 30
//基本思路：递归，设从起始位置到位置（xi,yi)处可行的最大路径为F(xi,yi),其值应等于F(xi-1,yi)+F(xi,yi-1);
//并且，该点与其前继电应当合法（isOk(xi,yi)==true);

typedef long long int ll;//要用type，斐波那契数列后面很大的
typedef struct{//储存点得信息的结构体
	int x;
	int y;
}point;
point wall,end,block[8];//三个全局结构变量

ll route[max][max];//记录到该点的路径数

const int change[2][8]={{-2,-2,-1,1,2,2,1,-1},{-1,1,2,2,1,-1,-2,-2}};//便于计算block位置的数组

bool isOK(int x,int y){//判断位置是否合法的函数
	if(x<0||x>end.x||y<0||y>end.y){//出界
		return false;
	}
	else if(x==wall.x&&y==wall.y){//撞人
		return false;
	}
	else{
	    for(int i=0;i<8;i++){//被断
		    if(x==block[i].x&&y==block[i].y){
			    return false;
		    }	
	    }
		return true;
    }
}	

ll ways(int x,int y){
	if(isOK(x,y)==false){//无效位置
        return 0;
	}
	else{     
	    if(route[x][y]!=-1){//有原始数据
		    return route[x][y];
	    }
	    else if(x==0&&y==0){//原点
		    route[x][y]=0;
		    return 0;
	    }
	    else if((x==1&&y==0)||(x==0&&y==1)){
	    	route[x][y]=1;
	    	return 1;
		}
	    else{//无原始数据
		    route[x][y]=ways(x-1,y)+ways(x,y-1);
		    return route[x][y];
	    }
    }

}	
int main(){
	memset(route,-1,sizeof(route));
	scanf("%d %d %d %d",&end.x,&end.y,&wall.x,&wall.y);
	for(int i=0;i<8;i++){
               block[i].x=wall.x+change[0][i];
	       block[i].y=wall.y+change[1][i];
	}
	printf("%lld\n",ways(end.x,end.y));
}
