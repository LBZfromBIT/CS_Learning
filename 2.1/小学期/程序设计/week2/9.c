#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//基本思路：本题算是上一题的一个强化般，即限制了该石头只能往平台上填；
//这就意味着，我们无法在数值高度上一次补2了，但我们依然可以依托平台，一层一层的往上加；
//因此本题本质上还是堆栈，只不过不用对高度进行转化01的预处理了（高度差%1是0）;
//需要注意的是，如果新进来的元素不能与栈顶匹配，并且比栈顶元素高的话，是肯定不能通过石头来填补的，此时直接break就好
//并且在最后，栈内必须是空栈或者只剩下一个最高点（画图想想这是为啥）

typedef long long int lli;
lli high[200005]={0};
lli box[200005]={0};

int main(){
	lli n;
	while(scanf("%lld",&n)!=EOF){
		memset(high,0,sizeof(high));
		memset(box,0,sizeof(box));
		//读入信息
		lli max=0;
		for(lli i=1;i<=n;i++){
			scanf("%lld",&high[i]);
			if(high[i]>max){
				max=high[i];
			}
		}
		//开始堆栈
		lli rest=0;//对栈内元素的统计
		for(lli i=1,place=1;i<=n;i++){//i指向high内元素，place指向栈顶
			if(rest==0){//空栈直接放
				box[place]=high[i];
				place++;
				rest++;
			}
			else{
				if(high[i]==box[place-1]){//遇到相同元素
                    box[place-1]=0;//弹出栈顶
					place--;
					rest--;			    
				}
				else{
					if(high[i]>box[place-1]){//新来的元素比栈顶大,横着补不了
						break;
					}
					else{//比栈顶小，下一个来横着可能补上
						box[place]=high[i];
					    place++;
					    rest++;
					}
				}
			}
		}
		if(rest==0){//栈空
			printf("YES\n");
		}
		else if(rest==1&&box[1]==max){//栈里只剩一个最大的
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
		
	}
}