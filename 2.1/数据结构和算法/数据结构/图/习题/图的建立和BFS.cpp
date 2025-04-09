#include <bits/stdc++.h>

//全局变量域
struct node{//结点结构
	char alpha;//结点对应的字母
	int anum;//结点对应的数字
	bool visit;//结点是否访问的标志
	int rel_bin;//有关的边数
	int chain[200];//储存有关的边
};
node table[200];//邻接表


//全局函数区域

//1.输出邻接表
void print_graph(node table[],int pnum){
	printf("the ALGraph is\n");
	for(int i=0;i<pnum;i++){
		printf("%c",table[i].alpha);
		if(table[i].rel_bin!=0){
			for(int j=table[i].rel_bin-1;j>=0;j--){
				printf(" %d",table[i].chain[j]);
			}
			printf("\n");
		}
		else{
			printf("\n");
		}
	}
	return;
}

//2.获得BFS
void BFS(node table[],int pnum){
	printf("the Breadth-First-Seacrh list:");
	std::queue<int> team;
	team.push(table[0].anum);
	table[0].visit=true;
	while(team.empty()!=true){
		int front=team.front();
		printf("%c",table[front].alpha);
		team.pop();
		if(table[front].rel_bin!=0){
			for(int i=table[front].rel_bin-1;i>=0;i--){
				int next=table[front].chain[i];
				if(table[next].visit==false){
					team.push(next);
					table[next].visit=true;
				}
				else{
					continue;
				}
			}
		}
		else{
			continue;
		}
	}
	for(int i=0;i<pnum;i++){
		if(table[i].visit==false){
			printf("%c",table[i].alpha);
		}
		else{
			continue;
		}
	}
	printf("\n");
	return;
}
int main(){
	//初始化录入信息
	char c;
	int pnum=0;
	scanf("%c\n",&c);
	while(c!='*'){
		table[pnum].alpha=c;
		table[pnum].anum=pnum;
		memset(table[pnum].chain,0,sizeof(table[pnum].chain));
		table[pnum].rel_bin=0;
		table[pnum].visit=false;
		pnum++;
		scanf("%c\n",&c);
	}
	//获取边的信息
	int start,end;
	scanf("%d,%d",&start,&end);
	while(start!=-1&&end!=-1){
		table[start].chain[table[start].rel_bin]=end;
		table[start].rel_bin++;
		table[end].chain[table[end].rel_bin]=start;
		table[end].rel_bin++;
		scanf("%d,%d",&start,&end);
	}
	//输出
	print_graph(table,pnum);
	BFS(table,pnum);
	return 0;
}