#include <bits/stdc++.h>
using namespace std;

//基本思路：
//https://blog.csdn.net/weixin_43787043/article/details/104525990

//全局变量区
#define M 100005//最大点数
typedef struct Node{//数据点
	double x;
	double y;
}node;
node point[M],temp[M];//存点数组point,暂存数组temp

//全局函数区

//两个比较函数
bool xcmp(node p1,node p2){
	return p1.x<p2.x;
}
bool ycmp(node p1,node p2){
	return p1.y<p2.y;
}

double cal(node p1,node p2){//计算两个点之间距离的函数
	double dx=p1.x-p2.x;
	double dy=p1.y-p2.y;
	double dis=sqrt(dx*dx+dy*dy);//两点距离
	return dis;
}

double mindis(int s,int e){//获得数组某个数据范围[s,e]内的点最小距离
	//递归终点1：如果范围内只有俩点了
	if(s+1==e){
		return cal(point[s],point[e]);
	}
	//递归终点2：如果仅含有三个点，直接遍历获得
	if(s+2==e){
		double d1=cal(point[s],point[s+1]);
		double d2=cal(point[s+1],point[e]);
		double d3=cal(point[s],point[e]);
		return min(d1,min(d2,d3));
	}
	//否则进入递归分治
	//先分
	int xmid=(s+e)/2;
	double d1=mindis(s,xmid);
	double d2=mindis(xmid+1,e);
	double d=min(d1,d2);
	
	//再治
	int ret=0;//记录在中轴点附近水平d距离的点的个数
	for(int i=s;i<=e;i++){
		if(fabs(point[i].x-point[xmid].x)<=d){
			temp[ret]=point[i];
			ret++;
		}
	}
	sort(temp,temp+ret,ycmp);//根据纵坐标排序
	for(int i=0;i<ret;i++){
		for(int j=i+1;j<ret;j++){
			if(temp[j].y-temp[i].y>=d){
				break;
			}
			else{
				d=min(d,cal(temp[i],temp[j]));
			}
		}
	}
	return d;
}

int main(){
	int num=0;
	scanf("%d",&num);
	for(int i=0;i<num;i++){
		scanf("%lf %lf",&point[i].x,&point[i].y);
	}
	//别忘了上来对x进行排序
	sort(point,point+num,xcmp);
	printf("%.2lf\n",mindis(0,num-1)/2);	
}