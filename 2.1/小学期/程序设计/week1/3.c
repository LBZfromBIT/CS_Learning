#include <stdio.h>
#include <stdlib.h>
//基本思路：利用二分法，将酒进行顺序编号，通过二分使得每只小鼠都能喝到混合多个酒桶的酒
//之后，可以知道，每个小鼠的死亡情况是唯一的，而可以通过小鼠喝酒时酒的重叠和老鼠的死亡情况对酒进行辨别
//若有M个小鼠，通过牛顿二项式定理，可以知道可能有2^M个死亡可能，每种可能都对应着一种酒的情况
//原题即求N<=2^M的最小整数解
//
//debug时发现，原题中酒最多有1e18，远超int的数据范围，因此加long long
//debug时还发现，当n=1时，是不用验证且一定有毒的，这种情况单列

int main(){
	int T=0;
	scanf("%d",&T);//测试案例数
	for(int i=1;i<=T;i++){
		long long int n;//酒的数量
		scanf("%lld",&n);
		if(n==1){
			printf("0\n");
		}
		else{
                        int m=1;//老鼠的数量，初始化为1
		        for(long long int status=1;;m++){
			        status=status*2;//tatus为可能方案数，求2^m
			        if(status>=n){
				     break;
			        }
		        }
		        printf("%d\n",m);
		}
        }
}
