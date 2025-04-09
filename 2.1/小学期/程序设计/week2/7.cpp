#include <bits/stdc++.h>

typedef long long int ll;
typedef struct{
	ll color;
	ll high;
}build;

build list[1000020];//存楼信息数组
ll cp[1000020];//验证颜色是否重复

std:: stack <build> a;

int main(){
	int time;
	scanf("%lld",&time);
	for(ll i=1;i<=time;i++){
		while(!a.empty()){//把盏清空
			a.pop();
	    }
		memset(list,0,sizeof(list));
		memset(cp,0,sizeof(cp));
		ll n;
		scanf("%lld",&n);
		for(ll i=1;i<=n;i++){//录入颜色
			scanf("%lld",&(list[i].color));
		}
		for(ll i=1;i<=n;i++){//录入高度
			scanf("%lld",&(list[i].high));
		}
		//本质是构建单调栈
		ll result=0;
		for(ll i=1;i<=n;i++){
			while(a.size()){//栈内别空
				build head=a.top();
				if(head.high<=list[i].high){//看不见的就弹出
					cp[head.color]--;//比对数组减一
					if(cp[head.color]==0){//当前颜色掉了，结果里减一
						result--;
					}
					a.pop();
				}
				else{//这里遇到高的就不用再找了，构成单调栈了，一定要赶紧退出，否则可能出不去循环
					break;
				}
			}
			a.push(list[i]);//进栈
			cp[list[i].color]++;//比对颜色
			if(cp[list[i].color]==1){//第一次出现的颜色
				result++;
			}
			
			if(i==n){
				printf("%lld\n",result);
			}
			else{
				printf("%lld ",result);
			}
		}
	}
}
