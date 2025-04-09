#include <bits/stdc++.h>

/*基本思路：
  采用回溯算法
  对每件物品采用拿和不拿两种策略
*/

//全局变量域
std::vector<int> solution;//存放最终解决方案的队列
std::vector<int> stage;//存放暂存方案的队列
int weigh[100050]={0};//存放重量的数组



//全局函数域
void stepback(int NO,int number,int& maxsum,int now_size,int max_size){
	if(now_size>max_size){//减枝，超重
		return;
	}
	else if(NO>number){//都考虑完了,
		if(now_size>maxsum){//出现更大项
			maxsum=now_size;
			solution.clear();
			for(auto p :stage){
				solution.push_back(p);
			}
			return;
		}
		else{
			return;
		}
	}
	else{
		//先考虑加入的情况
		stage.push_back(NO);
		stepback(NO+1,number,maxsum,now_size+weigh[NO],max_size);
		stage.pop_back();
		stepback(NO+1,number,maxsum,now_size,max_size);
		return;
	}
}


int main(){
	int max_size;
	int number;
	scanf("%d %d",&max_size,&number);
	for(int i=1;i<=number;i++){
		//从第一位开始
		scanf("%d",&weigh[i]);
	}
	//开始处理
	int maxsum=0;
	stepback(1,number,maxsum,0,max_size);
	printf("%d\n",maxsum);
	for(auto p :solution){
		printf("%d ",p);
	}
	printf("\n");
	 
}