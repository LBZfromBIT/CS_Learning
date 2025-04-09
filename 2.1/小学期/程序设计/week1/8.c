#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//基本思路：每拿到一个字符串后，看长度，如果长度不够就不管；长度够就存到数组里
//然后从低到高遍历数组，拿到每个字符串出现的第一个位置，比较当前位置判断是否有营养
char word[1024][32]={0};

int main(){
	int n=0;
    scanf("%d",&n);//有几句话
    getchar();//吃回车
	int number=0;//超过数量限制的字符数
	char single[32]={0};//分别读入每句话
	for(int i=1;i<=n;i++){
		memset(single,0,sizeof(single));
		gets(single);
		int lenth=strlen(single);//看长度
		if(lenth>10){
			number++;
			strcpy(word[number],single);
		}
	}
	int sum=0;//最后的计数器
	for(int i=number;i>=1;i--){//当前字符
		int first=i;
		for(int j=i-1;j>=1;j--){//向上遍历找第一
			if(strcmp(word[i],word[j])==0){
				first=j;
			}
		}
		if(first==i){
			sum++;
		}
	}	
	printf("%d\n",sum);
}
