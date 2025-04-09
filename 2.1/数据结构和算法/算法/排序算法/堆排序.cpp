#include <bits/stdc++.h>
using namespace std;

/*基本思路：构建大顶堆
    对数组中某点i 其父（i-1）/2； 左子2i+1;右子2i+2
    具体算法原理：https://zhuanlan.zhihu.com/p/124885051
*/

//全局函数区
void exchange(int* a,int* b){//交换两数函数
	int temp=*a;
	*a=*b;
	*b=temp;
}

void MC(int arr[],int start,int end){//在一个子树内调整的函数
	int dad=start;//父节点
	int son=2*dad+1;//最大子节点，先默认至左子节点
	while(son<=end){//子节点不超限
	    //左右节点比较，获得大子节点
		if(son+1<=end&&arr[son]<arr[son+1]){
			son=son+1;
		}
		//跟父节点比较
		if(arr[dad]>=arr[son]){
			return;//无需改变，直接返回
		}
		else{
			//交换，然后去比较改变的子节点与其下层节点
			exchange(&arr[dad],&arr[son]);
			dad=son;
			son=2*dad+1;
		}
	}
	
}
void HA(int arr[],int lenth){//获得最大堆的函数,lenth为非有序区间长度
	int i;
	for(i=lenth/2-1;i>=0;i--){
		MC(arr,i,lenth);
	}
	return;
}

int main(){
	int num;
	scanf("%d",&num);
	int* heap=new int[num+2];//堆的储存数组
	for(int i=0;i<num;i++){
		scanf("%d",&heap[i]);
	}
	//输出
	int time=0;
	while(time<3){
		int lenth=num-time;
		HA(heap,lenth-1);
		for(int i=0;i<lenth;i++){
			printf("%d ",heap[i]);
		}
		printf("\n");
		int temp;
		temp=heap[lenth-1];
		heap[lenth-1]=heap[0];
		heap[0]=temp;
		time++;
	}
	free(heap);
	return 0;
}