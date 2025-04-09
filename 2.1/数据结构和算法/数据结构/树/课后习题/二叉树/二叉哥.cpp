#include <bits/stdc++.h>
using namespace std;

/*基本思路：
       https://blog.csdn.net/qq_41680771/article/details/121062647
      先判断二叉树在这一层能不能满
      a.能满，那就输出2^n即可
      b.如果不满，则需要进行递归的对问题求解：
	  我们把问题模型转换->先每层至少一个，然后开始向右一层一层的填；
	  先看剩余的结点够不够填满以这一斜层为根节点所在行的二叉树，够的话就填满，更新层数并继续；
	  不够的话，转化为一个根节点在新位置下的求底层最大的填充问题-->递归解决
*/
//全局变量域
int answer=0;//答案

//全局函数域
void cal(int total,int level){//递归函数
	//先看看一行一个够不够
	if(total<level+1){//一行一个都不满，直接返回
		answer+=0;
		return;
	}
	else if(total==level+1){//一行一个刚好，尾行加1
		answer+=1;
		return;
	}
	else{//一行一个填完了，进行右补
	    total=total-(level+1);//更新余量
	    answer+=1;//至少一个
	    
		int layer=1;//当前层数tag;第0层根节点位置已经填充，从第一层开始往里放
		if(layer>level||total<=0){
			//超过层数或已经没有结点
			return;
		}
		int full;//放满该层需要的节点数
		full=pow(2,layer)-1;
		
		while(total-full>=0){//能放满就一直放
			answer+=pow(2,layer-1);//更新答案
			total=total-full;//更新total
			layer++;//层数上移
			full=pow(2,layer)-1;//更新full
			if(layer>level){//超过了层数就返回
				return;
			}
		}
		//退出时看是否还有total,有就递归;注意layer比函数中参数少一
        if(total!=0){
        	cal(total,layer-1);
		}
	   return;
	}
}

int main(){
	int time=0;
	scanf("%d",&time);
	while(time!=0){
		time--;
		int total,level;//总数，层数
		answer=0;//重置answer
		scanf("%d %d",&total,&level);
		//递归求解
		cal(total,level);
		printf("%d\n",answer);
	}
	return 0;
}