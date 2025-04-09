#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//思路源自：https://blog.csdn.net/weixin_43787043/article/details/108675129
//简述一下：由于石头1*2是固定的，但最后湖面的高度可以无限上叠，因此我们尽量去找补最高的那一列；
//而相邻的两个同高的湖面（称为平台）对填补湖面不影响（因为可以将石头横着放来填补），因此关键在于将（广义）相邻的列尽量补齐
//我们不妨以初始最高的列为0，看看不同高的列最多能补到与最高列相差多少（0或1），然后对01串来堆栈；
//根据第二行我们的理论，平台是不会对填补造成影响的，因而我们可以对相邻两个1或0消除，看最后栈内是否还有内容
//如果还有多于一个元素（一个元素的话可以竖着补），则永远补不了         
typedef long long int lli;
lli number[200005]={0};
lli box[200005]={0};

int main(){
	lli n;
	while(scanf("%lld",&n)!=EOF){//注意此处，EOF为一常量，当c语言处理文件输入到尾时即返回
	    lli max=0;
	    memset(number,0,sizeof(number));
	    memset(box,0,sizeof(box));
		for(lli i=1;i<=n;i++){
			scanf("%lld",&number[i]);
			if(number[i]>max){//在输入信息的同时拿到最大值
				max=number[i];
			}
		}
		for(lli i=1;i<=n;i++){//化为01串
			number[i]=(max-number[i])%2;
		}
		//准备堆栈
		lli rest=0;//栈内剩余数
		for(lli i=1,place=1;i<=n;i++){//place指向栈顶，i指向number内元素
			if(i==1||rest==0){//空栈时直接往里放
				box[place]=number[i];
				rest++;
				place++;
			}
			else{
				if(number[i]==box[place-1]){//进来的与栈顶相同
					box[place-1]=0;
					place--;
					rest--;
				}
				else{//进来的与栈顶不相同
					box[place]=number[i];
					rest++;
					place++;
				}
			}
		}
		if(rest<2){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}