#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int hand[300000]={0},desk[300000]={0};//记牌用数组

//思路来源：https://blog.csdn.net/m0_62573554/article/details/120603512

void change(long int hand[],long int desk[],long int n){
	int p=0;//0牌位置
	for(long int i=1;i<=n;i++){
		if(hand[i]==0){
			p=i;
			break;
		}
	}
	hand[p]=desk[1];//手牌+1
	for(long int i=1;i<n;i++){
		desk[i]=desk[i+1];//向前一位
	}
	desk[n]=0;//牌堆最底下搞0
}

int isS(long int hand[],long int desk[],long int n){//判断是否S条件
	for(long int number=1;number<=n;number++){
		int find=0;
		for(int i=1;i<=n;i++){
			if(number==hand[i]){
				find=1;
				break;
			}
		}
		for(long int i=1;i<=number-1&&find==0;i++){
			if(desk[i]==number){
				find=1;
				break;
			}
		}
		if(find==0){
			return 0;
		}
	}
	return 1;
}

int main(){
	long int n;
	scanf("%ld",&n);
	for(long int i=1;i<=n;i++){
		scanf("%ld",&hand[i]);
	}
	for(long int i=1;i<=n;i++){
		scanf("%ld",&desk[i]);
	}
	int isSort=1;
	long int last=desk[n];
	long int temp=last;
	for(long int i=n;temp>=1;temp--,i--){//部分有序为否
		if(temp!=desk[i]){
			isSort=0;
			break;
		}
	}
	if(isSort){//验证是否满足S'条件
		long int k=last;
		int result=0;
		for(long int i=1;i<=n;i++){//k+1必在手里
			if(hand[i]==k+1){
				result=1;
				break;
			}
		}
		if(result==0){
			isSort=0;
		}
		
		//k+i可以在手里，也可以在牌堆前i-1里
		for(long int j=2;j<=n-k;j++){
			int find=0;
			for(long int place=1;place<=n;place++){//在手里
				if(hand[place]==k+j){
					find=1;
					break;
				}
			}
			for(long int place=1;place<=j-1&&find==0;place++){//在排队里
				if(desk[place]==k+j){
					find=1;
					break;
				}
			}
			if(find==0){
				isSort=0;
				break;
			}
		}	
	}
	
	if(isSort){//可以直接往里搞牌了
		printf("%ld\n",n-last);
	}
	else{//去搞S条件
	    int step=0;
	    int status=0;
	    while(!status){
	    	change(hand,desk,n);
	    	step++;
	    	status=isS(hand,desk,n);
		}
		printf("%ld\n",step+n);
	}
}