#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//基本思路:用二维数组记录树的情况，通过选排将数据按成熟天数从早到晚排列，最后遍历，计算摘多少桃

int main(){
	int n=0,v=0;
	scanf("%d %d",&n,&v);//记录树的数量和每天摘多少

	int tree[3][n+1];//储存树的数据
	memset(tree,0,sizeof(tree));
	for(int column=1;column<=n;column++){//第一行为成熟日，第二行为桃的个数
		scanf("%d %d",&tree[1][column],&tree[2][column]);
	}
//接下来选排，按成熟早晚排序
	for(int column=1;column<n;column++){
		int min=column;
		for(int next=column+1;next<=n;next++){
			if(tree[1][next]<tree[1][min]){
				min=next;
			}
		}
		int temp=tree[1][column];
		tree[1][column]=tree[1][min];
		tree[1][min]=temp;
		temp=tree[2][column];
                tree[2][column]=tree[2][min];
		tree[2][min]=temp;
	}





//选排完，按天来收桃
        int day=0,rest=0;
	int sum=0;
	while(tree[2][n]!=0){//还有桃摘就不脱出
              day++;//场景初始化：天数+1；体力回满；腐烂桃子退场
	      rest=v; 
	      for(int i=1;i<=n;i++){
		      if(tree[1][i]<=day-2){
			      tree[2][i]=0;
		      }
	      }
//开始摘，体力清空就break,遇到没熟的就不摘；
	      for(int i=1;i<=n&&tree[1][i]<=day;i++){
		      if(tree[2][i]==0){
			      continue;
		      }
		      else if(rest==0){
                  break;
		      }
		      else if(rest<=tree[2][i]){
			      sum+=rest;
			      tree[2][i]=tree[2][i]-rest;
			      rest=0;
		      }
		      else{
			      sum+=tree[2][i];
			      rest=rest-tree[2][i];
			      tree[2][i]=0;
		      }
	      }

	}
        printf("%d\n",sum);
}
