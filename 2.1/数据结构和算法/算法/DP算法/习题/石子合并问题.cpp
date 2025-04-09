#include <bits/stdc++.h>


/*
基本思路：与矩阵连乘问题基本一致，将石子编号；
按照合并石子的堆数从少到多进行排布遍历，由于是圆形操场，考虑取模
*/

//全局变量域
#define M 105
int store[M]={0};//储存数组
int min[M][M]={0};//最小数组
int max[M][M]={0};//最大数组


//全局函数域
int getsum(int s,int e,int num){
	int sum=0;
	if(s==e){
		return s;
	}
	else{
		int i=s;
	    while(true){
		    sum+=store[i];
		    i=(i+1)%num;
		    if(i==(e+1)%num){
			    break;
		    }
	    }
	    return sum;
	}
}

int main(){
	int num=0;
	scanf("%d",&num);
	for(int i=0;i<num;i++){
		scanf("%d",&store[i]);
	}
	//初始化dp数组
	for(int i=0;i<num;i++){
		min[i][i]=0;
		max[i][i]=0;
	}
	//开始DP
	for(int lenth=2;lenth<=num;lenth++){//长度
		for(int s=0;s<num;s++){//起点从0到num-1
			int e=(s+lenth-1)%num;//确定终点
			int mini=INT_MAX;//最小值
			int maxi=INT_MIN;//最大值
			int sum=getsum(s,e,num);
			int pp=s;
			while(true){
				if(pp==e){
					break;
				}
				int res_min=min[s][pp]+min[(pp+1)%num][e]+sum;
				if(res_min<mini){
					mini=res_min;
				}
				int res_max=max[s][pp]+max[(pp+1)%num][e]+sum;
				if(res_max>maxi){
					maxi=res_max;
				}
				pp=(pp+1)%num;
			}
			min[s][e]=mini;
			max[s][e]=maxi;
		}
	}
	
	int ans_min=min[0][num-1];
	int ans_max=max[0][num-1];
	int x,y;
	for(int i=0;i<num;i++){
		if(min[i][(i+num-1)%num]<ans_min){
			ans_min=min[i][(i+num-1)%num];
			x=i;
			y=(i+num-1)%num;
		}
		if(max[i][(i+num-1)%num]>ans_max){
			ans_max=max[i][(i+num-1)%num];
		}
	}
	printf("%d\n",ans_min);
	printf("%d\n",ans_max);
}