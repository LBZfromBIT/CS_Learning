#include <bits/stdc++.h>//调用通配库
using namespace std;

//基本思路：https://blog.csdn.net/weixin_50295745/article/details/120255833
//由于成语接龙，一个成语的中间两个仅作区分意义，所以重点在于一头一尾


typedef long long int ll;//数据规模1e6,用long long
queue<ll> q;//队列
map<ll,vector<ll>> graph;//成语第一位为键，其可能的最后一位所构成的动数列为值的图
bool visit[1000050];
ll step[1000050];

int main(){
	ll m;
	scanf("%lld",&m);
	ll p1,p2;//成语的第一个和第四个
	ll b1,b2,b3,b4;//开始四位
	ll e1,e2,e3,e4;//结束四位
	for(int i=1;i<=m;i++){//录入开始的信息
		scanf("%lld %*lld %*lld %lld",&p1,&p2);
		graph[p1].push_back(p2);
	}
	scanf("%lld %lld %lld %lld",&b1,&b2,&b3,&b4);//开始词
	scanf("%lld %lld %lld %lld",&e1,&e2,&e3,&e4);//结束词
	if(b1==e1&&b2==e2&&b3==e3&&b4==e4){//自洽
		printf("1\n");
	}
	else if(b4==e1){//开始词和结束词连着
		printf("2\n");
	}
	else{//非特殊情况，bfs
		memset(step,-1,sizeof(step));
		memset(visit,false,sizeof(visit));
		q.push(b4);
		visit[b4]=true;
		step[b4]=1;
		while(!q.empty()){
			ll top=q.front();//记录队列的头，对应成语第一位
			q.pop();
			for(ll x:graph[top]){
				if(visit[x]==false){//对于未被遍历到的点
					q.push(x);
					visit[x]=true;
					step[x]=step[top]+1;
					if(top==e1&&x==e4){//恰好遍历到了答案
						break;
					}
					else if(top!=e1&&x==e4){//仅结尾相同而开头不同，说明走错了，该节点在之后仍可被访问
						step[x]--;
						visit[x]=false;
					}
				}
			}
		}
		printf("%lld\n",step[e4]);
	}
}