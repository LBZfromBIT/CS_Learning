#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//基本思路v1：对每一位遍历替换，然后匹配正则表达式，当匹配成功时返回答案，否则返回-1。
//结果：TLE，怀疑是正则表达式匹配的太多了，爆时间了

//基本思路v2：对每一位遍历替换，然后循环匹配字符串，匹配成功时返回答案，否则返回-1.
//结果：比刚才多过了1个，但还有几个TLE,代码的时间复杂度有点高

//基本思路v3：先看字符长度，小于10的直接-1；若多于10，从第一位开始向后循环，每次取10个，将得到的新串
//与目标字符串比较，看差几位：1.一点不差：这种情况不能不交换，在串内交换pp或tt即可
//                            2.差一位：只能从字符串外找一位换
//                            3.差两位：只能交换字符串内的两个，实现目标字符串
//                            3.差更多：一次交换不可能实现，直接-1

int check(char str1[],const char str2[],int place[]){//检测差异度函数
    int diff=0;
	for(int i=0;i<10;i++){
    	if(str1[i]!=str2[i]){
    		place[diff]=i;
			diff++;
		}
	}
	return diff;
}
int main(){
	int T;
	const char *stan="fattyhappy";
	scanf("%d",&T);//组数
	getchar();//吃回车
	char string[1050]={0};
	int place[10]={0};	
	for(int i=1;i<=T;i++){
		memset(place,0,sizeof(place));
		memset(string,0,sizeof(string));
		gets(string);
		int lenth=strlen(string);
		if(lenth<10){//长度肯定不足
			printf("-1\n");
		}
		else{
			int result=0;
			for(int head=0,tail=9;tail<lenth;head++,tail++){//从数组开头遍历
				int diff=0;//差异度
				char temp[20]={0};//暂存数组，别忘了初始化
				for(int i=head,j=0;i<=tail;i++,j++){
					temp[j]=string[i];
				}
				diff=check(temp,stan,place);
				if(diff==0){//一点不差的，交换tt
					printf("%d %d\n",head+3,head+4);
					result++;
					break;
				}
				else if(diff==1){//从外部找
				    int status=0,site=0;
					for(int i=0;i<lenth;i++){
						if(i>=head&&i<=tail){
							continue;
						}
						else{
							if(string[i]==stan[place[0]]){
								site=i;
								status=1;
								break;
							}
						}
					}
					if(status){
						printf("%d %d\n",head+place[0]+1,site+1);
						result++;
						break;
					}
				}
				else if(diff==2){//从内部找
					char bmp=temp[place[0]];
					temp[place[0]]=temp[place[1]];
					temp[place[1]]=bmp;
					if(strcmp(temp,stan)==0){
						printf("%d %d\n",head+place[0]+1,head+place[1]+1);
						result++;
						break;
					}
				}
			}
			if(!result){
				printf("-1\n");
			}
		}
    }
}