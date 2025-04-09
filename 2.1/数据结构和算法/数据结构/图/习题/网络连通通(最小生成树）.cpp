#include <bits/stdc++.h>
using namespace std;


/*基本思路：
  最小生成树问题，采用全局贪心的克鲁斯卡尔算法。
  即：
     先对所有的成本从小到大进行排序，
	 每次从中选一条未被选取且成本最小的边。
	 若此条边与之前选择的边不构成环，则将此边加入图中并计算开销
	 否则舍弃这条边而选择下一条成本最小的边。
  判断这条边与之前加入的边是否成环，我们可以借助并查集来进行判断。
*/

//全局变量域
struct pipe{
	int start;//起点
	int end;//终点
	int price;//价格
};
pipe team[5000];//储存管道数据的数组
queue <pipe> deb;



//全局函数域
bool cmp_price(pipe x,pipe y){//sort函数的比较函数
	return x.price<y.price;//从小到大排列
}

int* init(int N){//构建并查集函数(元素范围1~N)
    int* fa=(int*)malloc(sizeof(int)*(N+10));
	for(int i=0;i<=N;i++){
		fa[i]=i;//最开始并查集代表为自己
	}
	return fa;//返回表集指针
}

int find(int* fa,int a){//查找某个元素的代表元素
	if(fa[a]==a){//是代表元素
		return fa[a];
	}
	else{//是非代表元素
		return fa[a]=find(fa,fa[a]);//找其上层的代表元
	}
}

bool RoN(int x,int y,int* fa){//Ring or Not函数，判断当前边加入后是否变成环的函数
	int a=find(fa,x);//x的代表元
	int b=find(fa,y);//y的代表元
	if(a==b){
		return true;//在一环
	}
	else{
		fa[a]=b;//把代表元放一起
		return false;//不在一环
	}
}

int main(){
	//获得基本数据
	int N,M;//楼数N,管道数M
	scanf("%d %d",&N,&M);
	for(int i=0;i<M;i++){
		scanf("%d %d %d",&(team[i].start),&(team[i].end),&(team[i].price));
	}
	//用克鲁斯卡尔算法,先对数组按价格排序
	sort(team,team+M,cmp_price);
	int min_price=0;
	int select=0;//选择的管道数（共N个楼，需要N-1个管道)
	int* fa=init(N);
	for(int i=0;i<M;i++){
		if(RoN(team[i].start,team[i].end,fa)==false){//不构成环,写入
			min_price+=team[i].price;
			select++;
			deb.push(team[i]);
		}
		if(select==N-1){
			break;
		}
	}
	if(select!=N-1){
		min_price=-1;
	}
	printf("%d\n",min_price);
	free(fa);
	return 0;
	
}