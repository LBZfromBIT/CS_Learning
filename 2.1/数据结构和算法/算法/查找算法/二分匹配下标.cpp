#include <bits/stdc++.h>
using namespace std;

/*
基本思路：
        二分查找，三个指针left,mid,right
        1.如果T[mid]刚好等于mid,就存入数组，并在左右两侧搜索
        2.如果T[mid]<mid，就只搜索大于T[mid]侧
        3.如果T[mid]>mid,就只搜索小于T[mid]侧
*/

//全局变量域、
#define M 1000005
int T[M]={0};//储存数组
int S[M]={0};//记录数组

//全局函数域
void dc(int left,int right,int& number,bool status){
	//二分递归查找函数
	if(left<=right){
		int mid=(left+right)/2;
		if(T[mid]==mid){
			S[number]=mid;
			number++;
			dc(left,mid-1,number,status);
			dc(mid+1,right,number,status);
			return;
		}
		else if(T[mid]<mid){//值小下标大，只检索大于T[mid]侧
			if(status==true){//升序排布
				dc(mid+1,right,number,status);
			}
			else{
				dc(left,mid-1,number,status);
			}
			return;
		}
		else if(T[mid]>mid){//值大下标小，只检索小于T[mid]侧
			if(status==true){
				dc(left,mid-1,number,status);
			}
			else{
				dc(mid+1,right,number,status);
			}
			return;
		}
	}
	else{
		return;
	}
}

int main(){
	//录入信息
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&T[i]);
	}
	//判断升降序
	bool status;
	if(T[0]<=T[n-1]){
		status=true;
	}
	else{
		status=false;
	}
	//开始查找
	int number=0;
	dc(0,n-1,number,status);
	//输出
	if(number==0){
		printf("No \n");
	}
	else{
		sort(S,S+number);
		for(int i=0;i<number;i++){
			printf("%d ",S[i]);
		}
		printf("\n");
	}
}

