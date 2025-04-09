#include <bits/stdc++.h>
/*:
思路：
    使用贪心，用邻接表构建无向树的结构
    对叶子节点进行遍历，每次获得其父节点，并将士兵安排在父节点上
    之后删除该父节点和父节点所有的子节点
    知道删完为止
*/

//全局变量域
#define MAX 1501
typedef struct{
	int degree;//结点的度
	int next[MAX];//邻接点
	int bnum;//边数
}node;

//全局函数域
node* create(int sum){//建立邻接表的函数，传入参数为总共的结点个数
	//初始化表格
	node *table=new node[sum];
	for(int i=0;i<sum;i++){
		table[i].degree=0;
		memset(table[i].next,0,sizeof(table[i].next));
	}
	//录入信息
	int cnode,link,nnode;
	for(int i=0;i<sum;i++){
		scanf("%d:(%d)",&cnode,&link);
		for(int j=0;j<link;j++){
			scanf("%d",&nnode);
			table[cnode].next[table[cnode].degree]=nnode;
			table[cnode].degree++;
			table[cnode].bnum++;
			table[nnode].next[table[nnode].degree]=cnode;
			table[nnode].degree++;
			table[nnode].bnum++;
		}
	}
	return table;
}

int main(){
	int sum;//节点数
	while(scanf("%d",&sum)!=EOF){
		node* table=create(sum);
		int left=sum;//当前剩余未覆盖的节点数
		int soilder=0;//当前士兵数
		while(left>0){
			for(int i=0;i<sum;i++){
				if(table[i].degree==1){//为叶子结点
					table[i].degree=0;//摘叶子节点
					left--;//该点处理完毕
					
					//part2
					int father=0;//获得父节点
					while(father<table[i].bnum&&table[table[i].next[father]].degree==1){
						father++;
					}
					father=table[i].next[father];
					table[father].degree=0;
					soilder++;//安排一个士兵在父亲节点处
					left--;//摘父亲结点
					int anp=table[father].bnum;
					
					//part3
					for(int j=0;j<anp;j++){//处理所有邻接点
						int np=table[father].next[j];
						if(table[np].degree==1){//也是叶子点
							table[np].degree=0;
							left--;
						}
						else{
							table[np].degree--;
						}
					}
				}
			}
		}
		delete[] table;
		printf("%d\n",soilder);
	}
	
}