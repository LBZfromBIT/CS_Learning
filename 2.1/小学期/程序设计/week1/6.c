#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char result[1000000];//本题数组规模不给够，会报WA而非RE，不懂
char a[1000000],b[1000000];

//本题思路：
//将数字按字符串读入（高精度），然后按位进行运算，遇2进1位

void rev(char a[]){//字符串翻转函数
	int len=strlen(a);
	for(int head=0,tail=len-1;head<tail;head++,tail--){
		char temp='0';
		temp=a[head];
		a[head]=a[tail];
		a[tail]=temp;
	}
}
int max(int a,int b){
	if(a>=b){
		return a;
	}
	else{
		return b;
	}
}

int main(){
    int T=0;
    scanf("%d",&T);//输入组数
    for(int i=1;i<=T;i++){
    	//数据处理部分
    	memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));//加数a,加数b
    	scanf("%s %s",a,b);
    	int alen=strlen(a),blen=strlen(b);
    	
    	//结果生成部分
	    memset(result,0,sizeof(result));
	    rev(a);
	    rev(b);//将a,b反转便于计算
	    for(int i=0;i<max(alen,blen);i++){//遍历到两个数中大数的数位最高位
	    	if(result[i]=='1'){//该位有被进
	    		if(i>=alen){
	    			int temp=b[i]-48+1;
	    			if(temp>1){
	    				result[i]=(char)temp-2+48;
	    				result[i+1]='1';
					}
					else{
						result[i]=(char)temp+48;
					}
				}
				else if(i>=blen){
					int temp=a[i]-48+1;
	    			if(temp>1){
	    				result[i]=(char)temp-2+48;
	    				result[i+1]='1';
					}
					else{
						result[i]=(char)temp+48;
					}
				}
				else{
					int temp=a[i]-48+b[i]-48+1;
	    			if(temp>1){
	    				result[i]=(char)temp-2+48;
	    				result[i+1]='1';
					}
					else{
						result[i]=(char)temp+48;
					}
				}
			}
			else{//该位无被进
			    if(i>=alen){
	    			int temp=b[i]-48;
	    			if(temp>1){
	    				result[i]=(char)temp-2+48;
	    				result[i+1]='1';
					}
					else{
						result[i]=(char)temp+48;
					}
				}
				else if(i>=blen){
					int temp=a[i]-48;
	    			if(temp>1){
	    				result[i]=(char)temp-2+48;
	    				result[i+1]='1';
					}
					else{
						result[i]=(char)temp+48;
					}
				}
				else{
					int temp=a[i]-48+b[i]-48;
	    			if(temp>1){
	    				result[i]=(char)temp-2+48;
	    				result[i+1]='1';
					}
					else{
						result[i]=(char)temp+48;
					}
				}
			}
		}
		
		rev(a);//别忘了把a,b翻回来
		rev(b);
		rev(result);
		int width=strlen(result)+2;
		for(int i=1;i<=width-alen;i++){
			printf(" ");
		}
		puts(a);//第一行
		printf("+");
		for(int i=1;i<=width-1-blen;i++){
			printf(" ");
		}
		puts(b);//第二行
		for(int i=1;i<=width;i++){
			printf("-");
		}
		printf("\n");//第三行
		for(int i=1;i<=2;i++){
			printf(" ");
		}
		puts(result);
	}
}
