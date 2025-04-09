#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//以下俩个库为正则表达式函数库
#include <sys/types.h>
#include <regex.h>

//基本思路：对每一位遍历替换，然后匹配正则表达式，当匹配成功时返回答案，否则返回-1

int main(){
	const char *p="^.*fattyhappy.*$";//正则表达式
	int cflags=REG_EXTENDED;//匹配模式
	regex_t reg;//正则表达式字串结构体
	regcomp(&reg,p,cflags);//正则表达式编译
	regmatch_t pmatch[1];//储存匹配位置的结构体数组
	const size_t nmatch=1;//结构体数组长度
	int status;//匹配状态
	int T;
	scanf("%d",&T);
	getchar();
	char string[1050]={0};	
	for(int i=1;i<=T;i++){
		int time=0;
		memset(string,0,sizeof(string));
		gets(string);
		int lenth=strlen(string);
		for(int first=0;first<lenth;first++){//遍历比较
			for(int tail=first+1;tail<lenth;tail++){
				char temp;//进行交换
				temp=string[first];
				string[first]=string[tail];
				string[tail]=temp;
				status=regexec(&reg,string,nmatch,pmatch,0);
				if(status==0){//匹配成功
                    printf("%d %d\n",first,tail);
				    time++;
				    return 0;
				}
				else{//不成功
				    temp=string[first];//把字符串还原
			        string[first]=string[tail];
			        string[tail]=temp;
			        continue;	      
				}
			}
		}
		if(time==0){
			printf("-1\n");
		}
	}
}
