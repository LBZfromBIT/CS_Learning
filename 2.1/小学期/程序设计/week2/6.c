#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long int lli;
char temp[100005]={0};//记录输入的字符串
char can[100005]={0};
lli result=0;
lli self=0;
lli left[100005]={0};
lli right[100005]={0};
//基本思路（V1)：使用链表储存字符串，链表为空时往里插结点，否则就用新的信息与链表内各节点比较
//先判断左右括号合起来是否相等（不等则肯定不成立）
//然后将两个字符串拼接（有两个顺序都要考虑）存左括号，遇到右括号弹出；
//结果：出现了RE
//思路V2:来自https://blog.csdn.net/weixin_43787043/article/details/108518190，自行查看
//是对字符串一开始就进行了简化，同时在此处也要关心进栈的括号与前一个括号的顺序，单看数量会把'）（'也消掉

int box(char temp[],lli *rest){
	lli lenth=strlen(temp);
	lli lbox=0,rbox=0;
	for(lli i=0,before=0;i<lenth;i++){//before为栈顶指针
		if(temp[i]=='('){
			lbox++;
			can[before+1]=temp[i];
			before++;
		}
		else if(temp[i]==')'){
			if(lbox>0&&can[before]=='('){
				lbox--;
				can[before]=0;
				before--;
			}
			else{
				rbox++;
				can[before+1]=temp[i];
				before++;
			}
		}
	}
	if(lbox>0&&rbox>0){//无法匹配的，回2
	    *rest=0;
		return 2;
	}
	else if(lbox==rbox&&lbox==0){//自洽，回0
		*rest=0;
		return 0;
	}
	else if(lbox>0&&rbox==0){//全左
		*rest=lbox;
		return -1;
	}
	else if(rbox>0&&lbox==0){//全右
		*rest=rbox;
		return 1;
	}
}

lli min(lli a,lli b){
	if(a<=b){
		return a;
	}
	else{
		return b;
	}
}

int main(){
	lli result=0;
	lli n=0;
	scanf("%lld",&n);
	getchar();//吃换行
	//读入内容
	for(lli i=1;i<=n;i++){
		memset(temp,0,sizeof(temp));
		gets(temp);
		lli rest=0;
		int status=box(temp,&rest);//初步堆栈简化
		if(status==2){//无法匹配，直接跳过
			continue;
		}
		else if(status==-1){//全左
		    left[rest]++;
		}
		else if(status==1){//全右
			right[rest]++;
		}
		else if(status==0){//自洽
			self++;
		}		
	}
	for(int i=1;i<=100005;i++){
		result+=min(left[i],right[i]);
	}
	result+=(self/2);
	printf("%lld\n",result);
}