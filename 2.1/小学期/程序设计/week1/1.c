#include <stdio.h>//调用库
#include <stdlib.h>
#include <string.h>
#define max 20//指标数组最大值
//基本思路：使用数组array作为指标数组，通过字符串比较;
//在过大过小时，将相关数字标记，只有在right on,看该数字是否标记，以此来判断
int main(){
	int array[max]={0};
	int number=0;
	char answer[max]={0};
	char result[3][max]={"too low","too high","right on"};
	scanf("%d",&number);
	while(number){
		getchar();//吃空格
                gets(answer);
		if(!strcmp(answer,result[0])){//too low
			for(int i=1;i<=number;i++){
				array[i]++;
			}
                        memset(answer,0,sizeof(answer));//重置回答语句
			scanf("%d",&number);

		}
		else if(!strcmp(answer,result[1])){//too high
			for(int i=number;i<=10;i++){
				array[i]++;
			}
			memset(answer,0,sizeof(answer));
			scanf("%d",&number);
                }
		else if(!strcmp(answer,result[2])){//right on
			if(array[number]==0){
				printf("Tom may be honest\n");
			}
			else{
				printf("Tom is dishonest\n");
			}
			memset(array,0,sizeof(array));
			memset(answer,0,sizeof(answer));
			scanf("%d",&number);
		}
		else{
			printf("ERROR!\n");
			return 0;
		}
	}
}
