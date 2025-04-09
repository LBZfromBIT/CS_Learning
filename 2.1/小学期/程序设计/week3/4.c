//基本思路：二分查找（介于1与最大长度之间）
//相关原理：https://blog.csdn.net/zddwlig/article/details/119886256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100050

typedef long long int ll;

ll lenth[max]={0};//存长度数组

int check(ll *array,ll n,ll lenth,ll k){//检查函数
	ll num=0;//可能有多少根
	for(int i=0;i<n;i++){
		num+=(*array)/lenth;//除lenth取整，即为能切出来多少根
		array++;//指针指向下一位
	}
	if(num>=k){
		return 1;
	}
	else{
		return 0;
	}
}

int llsort(const void*a,const void *b){//升序快排函数
	return *(ll*)a>*(ll*)b?1:-1;
}
int main(){
	ll num;
	scanf("%lld",&num);
	for(ll i=1;i<=num;i++){
		scanf("%lld",&lenth[i]);
	}
	ll k;//要切出来绳子的个数
	scanf("%lld",&k);
	//为二分查找做准备->快排一下
	qsort(&lenth[1],num,sizeof(ll),llsort);
	//准备进行二分查找，其中会调用检查函数
	ll low=1,high=lenth[num];//low为二分下界，high为二分上界
	ll result=0;//最终结果，默认为0（即无法切割）
	while(low<=high){//二分脱出条件：下界不超过上界
		ll mid=(low+high)/2;//二分中线
		if(check(&lenth[1],num,mid,k)==1){//当前mid可以，为一可能值，并且可能更长
			if(mid>result){
				result=mid;
			}
			low=mid+1;//二分下界右移
		}
		else{//当前mid不行，但其左侧可能有符合
			high=mid-1;
		}
	}
	printf("%lld\n",result);
}