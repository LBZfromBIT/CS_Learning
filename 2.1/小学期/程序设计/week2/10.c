#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//思路来源：https://blog.csdn.net/m0_74200772/article/details/132622678
//简述一下：即为每个人都有两个参量：是否进栈参选和是否投票否决；
//而出于最优目的，在前面的人会尽量参选，并否决后面的异族人；
//而后面存活的人会尽量使用否决权来让前面的异族人出栈
typedef long long int ll;
char string[200050]={0};//记录排列
char box[200050]={0};//记录还有谁具有选举权
ll td=0,tx=0;//记录各族还有多少人有投票权(没被前面的异族人一票否决）
int main(){
	ll n;//总人数
	scanf("%lld",&n);
	getchar();
	gets(string);
	ll top=0;//栈顶下标
	for(ll i=0;i<n;i++){
		if(string[i]=='D'){//D族人
			if(tx==0){//X族人没有投票否决权，D能够进栈
			    //接下来要看栈顶是否为异族人
			    if(box[top]=='X'){
			    	box[top]=0;
			    	top--;
			    	ll num=1;
			    	while(i<n-1&&string[i+1]=='D'&&top!=0&&box[top]=='X'){//注意此处，是判断下一个是否为同族人而非当前这个（因为i会随着动，如果比较当前位置的话，会导致i最后停在不一样的族人上，在下一轮就会导致跳过了）
			    		box[top]=0;
			    		top--;
			    		num++;
			    		i++;
					}
					while(num>0){
						box[top+1]='D';
						top++;
						num--;
					}
				}
				else{//不然就正常进栈，D票+1
			        box[top+1]='D';
					top++;
					td++;	
			    }
		    }
			else{//X族人有投票权，把该D族人取消了，X投票权-1
				tx--;
			}
		}
		else if(string[i]=='X'){//X族人
			if(td==0){//D族人没有投票否决权，x能够进栈
			    //接下来要看栈顶是否为异族人
			    if(box[top]=='D'){
			    	box[top]=0;
			    	top--;
			    	ll num=1;
			    	while(i<n-1&&string[i+1]=='X'&&top!=0&&box[top]=='D'){
			    		box[top]=0;
			    		top--;
			    		num++;
			    		i++;
					}
					while(num>0){
						box[top+1]='X';
						top++;
						num--;
					}
				}
				else{//不然就正常进栈，x票+1
			        box[top+1]='X';
					top++;
					tx++;	
			    }
		    }
			else{//D族人有投票权，把该X族人取消了，D投票权-1
				td--;
			}
		}
	}
	
	ll drest=0,xrest=0;//两族还剩多少竞选人
	for(int i=1;i<=top;i++){
		if(box[i]=='D'){
			drest++;
		}
		else{
			xrest++;
		}
	}
	if(drest>xrest){
		printf("D\n");
	}
	else if(drest<xrest){
		printf("X\n");
	}
	else{
		printf("%c\n",box[1]);
	}
}
