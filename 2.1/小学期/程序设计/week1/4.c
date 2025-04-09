#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//基本思路：首先鸣谢学姐的巧妙思路讲解
//详见site:https://blog.csdn.net/weixin_43787043/article/details/108481712
//
//用我的话转述一下：
//本题的核心在于，判断该数表上某一行空白位置的最大连续长
//度，并同时确保严格的上下层关系（上层完成才能做下层）。
//那么我们不妨先将我们需要挖去的部分表示出来，如下面图表
//
//
//  3 |1 1 1 1 1 1
//  2 |1 1 1   1 1    *挖去部分为图中的1
//  1 |1   1     1     此时图为正的，仍要满足先上后下
//    ————————————
//     1 2 3 4 5 6
//
//
//那我们不妨将图的每一列上下颠倒，然后规则变成满足先下后上
//如下图
//
//
//   3 |1   1     1   
//   2 |1 1 1   1 1    *此时挖去部分还是图中的1
//   1 |1 1 1 1 1 1     此时图为倒的，要满足先下后上
//     ————————————
//      1 2 3 4 5 6
//
//
// 用单列数组表示要挖去的部分既为[3,2,3,1,2,1]
// 接下来，我们这么考虑一下：
//
// （1）.我们先设置一个至少需要的天数-->即数组的第一元素大小
//       因为这三层不可能同一天完成（先下后上），所以至少3天。
//       
// （2）.[高潮来啦！]从第二个元素开始，我们将该元素大小与上一个
//       进行比较，如果小于上一个，意味着可以在同一天被上一列的
//       铲车一同铲完；如果大于上一个，则意味着这一列挖着比上一
//       列更深，需要补充天数=两者高度差；
//
// （3）.就这么遍历下去，就能完成任务啦！！！


int main(){
	long long int wide=0,high=0;
	scanf("%lld %lld",&wide,&high);//输入宽度wide，初始高度high
	long long int basic[wide+1];
	memset(basic,0,sizeof(basic));
	for(int i=1;i<=wide;i++){//读入地面高度列表，并且直接转化为清除的个数列表
		if(i!=wide){
			scanf("%lld ",&basic[i]);
			basic[i]=high-basic[i];
		}
		else{
			scanf("%lld",&basic[i]);
			basic[i]=high-basic[i];
		}
	}
	//接下来，进入算法的高潮！！！
	long long int day=basic[1];
	for(int i=2;i<=wide;i++){
		if(basic[i]<=basic[i-1]){
			continue;
		}
		else{
			day+=basic[i]-basic[i-1];
		}
	}
	printf("%lld\n",day);
}
