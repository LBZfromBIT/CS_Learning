#include <bits/stdc++.h>

/*基本思路：
  按照哈夫曼树的构造原理：在所有结点中挑两个最小的合成树
  我们可以直接用优先数组--
  （在优先队列中，元素被赋予优先级。
  当访问元素时，具有最高优先级的元素最先删除。
  优先队列具有最高级先出 （first in, largest out）的行为特征。
  对于普通的数值来说，数值越大，优先级越高。）
  来对所有的结点值进行储存，每次弹出两个最小的求和，将和加回到优先队列中；
  关于WPL的计算：可以证明，一个哈夫曼树的WPL即为其所有非根结点的权值之和；
  
  不断重复此过程，对于n个结点来说，此过程要进行n-1次；
*/

//全局函数域
int WPL(int n){//计算WPL的函数
	std::priority_queue< int , std::vector<int> , std::greater<int> > team;//建立升序的优先队列
	int weight;
	for(int i=0;i<n;i++){//输入数据进队列
		scanf("%d",&weight);
		team.push(weight);
	}
	//开始计算WPL
	int sum=0;
	for(int i=1;i<n;i++){//共n-1次
		int result=0;
		result+=team.top();//加入第一个最小数
		team.pop();
		result+=team.top();//加入第二个最小数
		team.pop();
		sum+=result;//和计入结果
		team.push(result);//和放入队伍
	}
	return sum;
}

int main(){
	int n=0;
	scanf("%d\n",&n);
	printf("WPL=%d\n",WPL(n));
	return 0;
}