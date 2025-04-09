#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char a[4000]={0},b[4000]={0};
char a1[4000]={0},a2[4000]={0};
char b1[4000]={0},b2[4000]={0};
char r1[4000]={0},r2[4000]={0};

//基本思路：将加数和被加数都拆成整数和小数两个数组
//先做小数部分计算，最高位进位则在整数部分开始计算时加1

void rev(char a[]){
	int lenth=strlen(a);
	for(int head=0,tail=lenth-1;head<tail;head++,tail--){
		int temp=0;
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
    gets(a);
    gets(b);
    //先看是小数还是整数
    int aflag=1,bflag=1;//整数为1，小数时为0
    int alen=strlen(a),blen=strlen(b);
    for(int i=0;i<alen;i++){
    	if(a[i]=='.'){
    		aflag=0;
    		break;
		}
	}
	for(int i=0;i<blen;i++){
		if(b[i]=='.'){
			bflag=0;
			break;
		}
	}
	if(aflag&&bflag){//mode1:俩整数，去前零直接算，存r1里，
	    //先去零
	    int place=0,site=0;
	    for(;place<alen;place++){//从a开始
		    if(a[place]!='0'){
		    	site=place;
			    break;
		    }
		    else if(place==alen-1){
		    	site=place;
			}
	    }
	    for(int i=site,j=0;i<alen;i++,j++){
	    	a1[j]=a[i];
		}
		place=0;
		site=0;
		for(;place<blen;place++){
			if(b[place]!='0'){
				site=place;
				break;
			}
			else if(place==blen-1){
				site=place;
			}
		}
		for(int i=site,j=0;i<blen;i++,j++){
	    	b1[j]=b[i];
		}
		
	    int a1len=strlen(a1),b1len=strlen(b1);
		rev(a1);
		rev(b1);
		for(int i=0;i<max(a1len,b1len);i++){
			int temp;
			if(r1[i]=='1'){
				if(i>=a1len){
					temp=b1[i]-48+1;
				}
				else if(i>=b1len){
					temp=a1[i]-48+1;
				}
				else{
					temp=a1[i]-48+b1[i]-48+1;
				}
				if(temp>=10){
					r1[i]=(char)temp-10+48;
					r1[i+1]='1';
				}
				else{
					r1[i]=(char)temp+48;
				}
			}
			else{
				if(i>=a1len){
					temp=b1[i]-48;
				}
				else if(i>=b1len){
					temp=a1[i]-48;
				}
				else{
					temp=a1[i]-48+b1[i]-48;
				}
				if(temp>=10){
					r1[i]=(char)temp-10;
					r1[i+1]='1';
				}
				else{
					r1[i]=(char)temp+48;
				}
		    }
		}
		rev(a1);
		rev(b1);
		rev(r1);
		
		int r1len=strlen(r1);
		int width=max(r1len,max(alen,blen))+3;
		//第一行
		for(int i=1;i<=width-alen;i++){
			printf(" ");
		}
		for(int i=0;i<alen;i++){
			printf("%c",a[i]);
		}
		printf("\n");
		//第二行
		printf("+");
		for(int i=1;i<=width-blen-1;i++){
			printf(" ");
		}
		for(int i=0;i<blen;i++){
			printf("%c",b[i]);
		}
		printf("\n");
		//第三行
		for(int i=1;i<=width;i++){
			printf("-");
		}
		printf("\n");
		//第四行
		for(int i=1;i<=width-r1len;i++){
			printf(" ");
		}
		for(int i=0;i<r1len;i++){
			printf("%c",r1[i]);
		}
		printf("\n");
	}
	else{//mode2:小数运算
	    //从这开始提取a1,a2,b1,b2
		if(aflag==1&&bflag==0){
			strcpy(a1,a);
			char *p=strtok(b,".");
			for(int i=1;i<3;i++,p=strtok(NULL,".")){
				if(i==1){
					strcpy(b1,p);
				}
				else{
					strcpy(b2,p);
				}
			}
		}
		else if(bflag==1&&aflag==0){
			strcpy(b1,b);
			char *p=strtok(a,".");
			for(int i=1;i<3;i++,p=strtok(NULL,".")){
				if(i==1){
					strcpy(a1,p);
				}
				else{
					strcpy(a2,p);
				}
			}
		}
		else{
			char *p=strtok(a,".");
			for(int i=1;i<3;i++,p=strtok(NULL,".")){
				if(i==1){
					strcpy(a1,p);
				}
				else{
					strcpy(a2,p);
				}
			}
			char *q=strtok(b,".");
			for(int i=1;i<3;i++,q=strtok(NULL,".")){
				if(i==1){
					strcpy(b1,q);
				}
				else{
					strcpy(b2,q);
				}
			}
		}
		
		//先看小数部分
	    //先将小数部分精度补齐
	    int a2len=strlen(a2),b2len=strlen(b2);//原始的a2,b2长度,输出时控制用
	    if(a2len>b2len){
		    for(int i=b2len;i<a2len;i++){
			   b2[i]='0';
		    }
	    }
	    else{
		    for(int i=a2len;i<b2len;i++){
			   a2[i]='0';
		    }
	    }
	    int lenth=strlen(a2);
	    //再将数组反转计算
	    rev(a2);
	    rev(b2);
	    for(int i=0;i<lenth;i++){
		    if(r2[i]=='1'){
			   int number=a2[i]-48+b2[i]-48+1;
		       if(number>=10){
			       r2[i]=(char)(number-10+48);
			       r2[i+1]='1';
		        }
		        else{
			       r2[i]=(char)(number+48);
		        }
		    }
		    else{
			    int number=a2[i]-48+b2[i]-48;
		        if(number>=10){
			       r2[i]=(char)(number-10+48);
		 	       r2[i+1]='1';
		        }
		        else{
			       r2[i]=(char)(number+48);
		        }
		    }
	    }
	    int status=0;//小数修正量
	    if(strlen(r2)>lenth){//说明得补整数
		    status=1;
		    r2[lenth]=0;
		    rev(r2);
	    }
	    else{
		    rev(r2);
	    }
		rev(a2);
		rev(b2);//注意此时，所有小数的长度均为lenth（a2,b2.r2)
	
	    //接下来处理整数部分
	    //先把去先导零的纯整数数组拿到，传回到a,b里进行重复利用
	    int a1len=strlen(a1);
	    int b1len=strlen(b1);
	    memset(a,0,sizeof(a));
	    memset(b,0,sizeof(b));
	    int place=0,site=0;
	    for(;place<a1len;place++){//从a开始
		    if(a1[place]!='0'){
		    	site=place;
			    break;
		    }
		    else if(place==a1len-1){
		    	site=place;
			}
	    }
	    for(int i=site,j=0;i<a1len;i++,j++){
	    	a[j]=a1[i];
		}
		place=0;
		site=0;
		for(;place<b1len;place++){
			if(b1[place]!='0'){
				site=place;
				break;
			}
			else if(place==b1len-1){
				site=place;
			}
		}
		for(int i=site,j=0;i<b1len;i++,j++){
	    	b[j]=b1[i];
		}
		
		//然后颠倒a,b，开始计算整数部分值(注意别忘了小数修正量）
		rev(a);
		rev(b);
		if(status==1){
			r1[0]='1';
		}
		for(int i=0;i<max(strlen(a),strlen(b));i++){
			int temp;
			if(r1[i]=='1'){
				if(i>=strlen(a)){
					temp=b[i]-48+1;
				}
				else if(i>=strlen(b)){
					temp=a[i]-48+1;
				}
				else{
					temp=a[i]-48+b[i]-48+1;
				}
				if(temp>=10){
					r1[i]=(char)temp-10+48;
					r1[i+1]='1';
				}
				else{
					r1[i]=(char)temp+48;
				}
			}
			else{
				if(i>=strlen(a)){
					temp=b[i]-48;
				}
				else if(i>=strlen(b)){
					temp=a[i]-48;
				}
				else{
					temp=a[i]-48+b[i]-48;
				}
				if(temp>=10){
					r1[i]=(char)temp-10+48;
					r1[i+1]='1';
				}
				else{
					r1[i]=(char)temp+48;
				}
			}
		}
		rev(r1);//得到整数部分
		
		//接下来到输出部分了
		int width=lenth+max(strlen(r1),max(a1len,b1len))+4;//总宽度=最长小数+最长整数(包括算完了）+点+3（加号和俩空格）
		//第一行
		for(int i=1;i<=width-a1len-1-lenth;i++){
			printf(" ");
		}
		for(int i=0;i<a1len;i++){
			printf("%c",a1[i]);
		}
		if(aflag==0){
			printf(".");
		}
		else{
			printf(" ");
		}
		for(int i=0;i<a2len;i++){
			printf("%c",a2[i]);
		}
		for(int i=1;i<=lenth-a2len;i++){
			printf(" ");
		}
		printf("\n");
		//第二行
		printf("+");
		for(int i=1;i<=width-b1len-2-lenth;i++){
			printf(" ");
		}
		for(int i=0;i<b1len;i++){
			printf("%c",b1[i]);
		}
		if(bflag==0){
			printf(".");
		}
		else{
			printf(" ");
		}
		for(int i=0;i<b2len;i++){
			printf("%c",b2[i]);
		}
		for(int i=1;i<=lenth-b2len;i++){
			printf(" ");
		}
		printf("\n");
		//第三行
		for(int i=1;i<=width;i++){
			printf("-");
		}
		printf("\n");
		//第四行
		int r1len=strlen(r1);
		for(int i=1;i<=width-r1len-1-lenth;i++){
			printf(" ");
		}
		for(int i=0;i<r1len;i++){
			printf("%c",r1[i]);
		}
		printf(".");
		for(int i=0;i<lenth;i++){
			printf("%c",r2[i]);
		}
		for(int i=1;i<=lenth-lenth;i++){
			printf(" ");
		}
		printf("\n");
	}	
}