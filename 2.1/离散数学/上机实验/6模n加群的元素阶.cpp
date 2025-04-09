#include <bits/stdc++.h>
using namespace std;

//基本思路：
//在模n加群里，元素的阶=元素/（元素与n的最大公约数）、

int mc(int small,int big){//辗转相处出最大公约数
	while(big%small!=0){
		int temp=big%small;
		big=small;
		small=temp;
	}
	return small;
}

int main(){
	int num;
	int x;
	scanf("%d,%d",&num,&x);
	if(x==0){
		printf("1\n");
	}
	else{
		printf("%d\n",num/mc(x,num));
	}
}