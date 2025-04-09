#include <bits/stdc++.h>

/*思路:
   构建两个搜索表：前查表和后查表；
   |->前查表中记录该结点前面有什么点
   |->后查表记录该节点后面有什么点
   在判断极大元时，搜索后查表，找到后面没有点的点即为极大元
   在判断极小元时，搜索前查表，找到前面没有点的点即为极小元
*/

//全局变量域
typedef struct node{
	char point;//点的名字
	int num;//点的后继数量
	char array[30];//点的后继表
};
node back[30];//后查表
node front[30];//前查表

//全局函数域
//1.获得点的数量和初始化
int number(char bas[]){
	int lenth=strlen(bas);
	int num=0;
	for(int i=0;i<lenth;i++){
		if(bas[i]>='a'&&bas[i]<='z'){
			num++;
			back[bas[i]-97].num=0;
			back[bas[i]-97].point=bas[i];
			front[bas[i]-97].num=0;
			front[bas[i]-97].point=bas[i];
		}
		else{
			continue;
		}
	}
	return num;
}

//2.处理关系函数
void deal(char ral[]){
	int lenth=strlen(ral);
	std::stack<char> freeze;//存关系的栈
	for(int i=0;i<lenth;i++){
		if(ral[i]>='a'&&ral[i]<='z'){//是字母
			if(freeze.empty()==true){//是前件
				freeze.push(ral[i]);
			}
			else{//是后件
			    freeze.push(ral[i]);
				int after=(int)freeze.top()-97;
				freeze.pop();
				int before=(int)freeze.top()-97;
				freeze.pop();
				//开始写表
				front[after].array[front[after].num]=before;//前查表
				front[after].num++;
				back[before].array[back[before].num]=after;//后查表
				back[before].num++;
			}
		}
		else{
			continue;
		}
	}
	return;
}

int main(){
	char bas[50]={0};
	gets(bas);
	int num=number(bas);
	
	char ral[100]={0};
	gets(ral);
	deal(ral);
	
	//遍历两表即可
	std::queue<char> mini;//极小元
	std::queue<char> maxi;//极大元
	for(int i=0;i<num;i++){
		if(front[i].num==0){
			mini.push(front[i].point);
		}
		if(back[i].num==0){
			maxi.push(back[i].point);
		}
	}
	while(mini.empty()!=true){
		char cp=mini.front();
		mini.pop();
		printf("%c",cp);
		if(mini.empty()==true){
			printf("\n");
		}
		else{
			printf(",");
		}
	}
	while(maxi.empty()!=true){
		char cp=maxi.front();
		maxi.pop();
		printf("%c",cp);
		if(maxi.empty()==true){
			printf("\n");
		}
		else{
			printf(",");
		}
	}
}