#include <bits/stdc++.h>
using namespace std;
//思路来源：
//https://blog.csdn.net/weixin_43787043/article/details/104530024

//全局变量区
#define M 2000005//最大油井数量
int col[M]={0};//储存纵坐标的数组

//全局函数
void ssort(int s,int e){//选择排序函数,升序排列
	for(int i=s;i<e;i++){
		int mo=i;
		for(int j=i+1;j<=e;j++){
			if(col[mo]>col[j]){
				mo=j;
			}
			else{
				continue;
			}
		}
		swap(col[mo],col[i]);
	}
	return;
}

int FindP(int s,int e){//返回pivot值
	int g=0;//组数
	int i=0;
	for(i=s;i+4<=e;i=i+5){//5个一组，获得中位数，并调整到数组前，便于之后递归的进行求解
		ssort(i,i+4);//组内先排序
		swap(col[s+g],col[i+2]);//交换到最前面(但是是从s开始）
		g++;
	}
	//注意，e-s可能不被5整除，需要对后面内容再处理
	if(i<e){
		ssort(i,e);
		int mid=(e+i)/2;
		swap(col[s+g],col[mid]);
		g++;
	}
	//递归终点->筛出来的中位数仅仅就剩下零组或一组了
	if(g<=1){
		return col[s];
	}
	else{
		return FindP(s,s+g-1);
	}
}

int GetP(int s,int e,int val){//获得pivot的数组下标
	for(int i=s;i<=e;i++){
		if(col[i]==val){
			return i;
		}
	}
}

int Partition(int s,int e){//Partition过程,使用hoare方式
	int pivot=FindP(s,e);//获得pivot值
	int place=GetP(s,e,pivot);//获得pivot位置
	swap(col[e],col[place]);//交换pivot至最后，便于partition
	int small=s,big=e-1;//前后双指针，small指小数，big指大数
	while(small<big){//当小指针不过大指针时
		while(small<=e-1&&col[small]<=pivot){//i从前向后停在大于pivot值
			small++;
		}
		while(big>=s&&col[big]>=pivot){//从后向前停在小于pivot值
			big--;
		}
		if(small<big){//检查一下，是否指针未错位
			swap(col[small],col[big]);
		}
	}
	//最终考虑换下位置,此时s到e-1都已排好，左到右找到第一个大于pivot的数字
	swap(col[e],col[small]);
	return small;//返回pivot的位置
}

int BFPTR(int s,int e,int goal){//BFPTR算法
	int pplace=Partition(s,e);//pivot位置
	int num=pplace-s+1;//含piplace前面有多少个值
	if(num==goal){//刚好
		return col[pplace];
	}
	else if(num>goal){//过了
		return BFPTR(s,pplace-1,goal);
	}
	else{//没到
	    return BFPTR(pplace+1,e,goal-num);
	}
}

int main(){
	int Number=0;
	int x=0,y=0;
	while(scanf("%d,%d",&x,&y)!=EOF){
		col[Number]=y;
		Number++;
	}
	int ans=BFPTR(0,Number-1,(1+Number)/2);
	printf("%d\n",ans);
}