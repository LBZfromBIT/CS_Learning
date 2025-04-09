#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//思路：贪心算法+快速排序，每次选择结束时间最早的不冲突的任务完成
typedef struct mission{//储存开始和结束时间的结构体
	long long int begin;
	long long int end;
}Mission;
Mission time[300001];//记录数据的数组

int lower(const void *a,const void *b){
	return (*(Mission*)a).end>(*(Mission*)b).end?1:-1;
}


int main(){
	int n=0;
	memset(time,0,sizeof(time));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&(time[i].begin),&(time[i].end));
	}
	//按结束时间进行排序，使用快排函数
	qsort(&time[1],n,sizeof(Mission),lower);
	int count=1;
	for(int i=2,j=1;i<=n;i++){//此处贪心算法，i指向当前任务，j指向前一个已完成的任务而非上一个任务
		if(time[i].begin>=time[j].end){
			count++;
			j=i;
		}
	}
	printf("%d\n",count);
}