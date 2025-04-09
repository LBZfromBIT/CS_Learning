#include <bits/stdc++.h>
using namespace std;

//全局变量域
int arr[200]={0};//储存数字用数组
int median[200]={0};//储存中轴用数组
int mnum=0;//meddin计数器

//全局函数域
int StN(char str[]){//字符串转数字
	bool neg=false;
	if(str[0]=='-'){
		neg=true;
	}
	
	int lenth=strlen(str);
	if(neg==true){
		int sum=0;
		for(int i=1;i<lenth;i++){
			sum=10*sum+(str[i]-'0');
		}
		return 0-sum;
	}
	else{//正的
		int sum=0;
		for(int i=0;i<lenth;i++){
			sum=10*sum+(str[i]-'0');
		}
		return sum;
	}
}

int get_med(int start,int end){//取medain值函数
	int mid=(start+end)/2;//中间
	int meddin=0;
	if(arr[start]>arr[end]){//a>c
		if(arr[mid]>arr[end]){//b>c
			if(arr[mid]>arr[start]){//b>a>c
				meddin=arr[start];
			}
			else{//a>b>c
				meddin=arr[mid];
				swap(arr[mid],arr[start]);
			}
		}
		else{//a>c>b
			meddin=arr[end];
			swap(arr[end],arr[start]);
		}
	}
	else{//a<c
		if(arr[mid]<arr[end]){//b<c
			if(arr[start]<arr[mid]){//a<b<c
				meddin=arr[mid];
				swap(arr[mid],arr[start]);
			}
			else{//b<a<c
				meddin=arr[start];
			}
		}
		else{//a<c<b
			meddin=arr[end];
			swap(arr[end],arr[start]);
		}
	}
	//存入数据
	median[mnum]=meddin;
	mnum++;
	return meddin;
}

int sort(int start,int end){//ROWE算法排序，返回pivot位置
    int pivot=get_med(start,end);//pivot值，此时pivot位置在arr[start]
    int place=start+1;//place先定位到第一个大于pivot的位置
    while(place<=end&&arr[place]<=pivot){
    	place++;
	}
	int com=place+1;//com指向小于pivot的值

	while(com<=end){//上界
		if(arr[com]<pivot){//当前com小于pivot
		    //交换位置
			int temp=arr[com];
			arr[com]=arr[place];
			arr[place]=temp;
			place++;
			
			//更新指针
			while(place<=end&&arr[place]<=pivot){
    	        place++;
	        }
			com=place+1;
			continue;
		}
		else{
			com++;
			continue;
		}
	}
	
	//最终从前向后遍历一边，换pivot位置
	int final=start;
	while(final<end&&arr[final+1]<=pivot){
		final++;
	}
	swap(arr[final],arr[start]);
	return final;
}

void insert(int start,int end){//插入排序函数
	int dp=start;//有序和无序分割位
	while(dp<end){//无序取仍然有数
		int place=start;
		while(place<=dp&&arr[place]<=arr[dp+1]){
			place++;
		}
		if(place!=dp+1){//此时需要调整
			int temp=arr[dp+1];//暂存一下
			for(int i=dp+1;i>place;i--){
				arr[i]=arr[i-1];
			}
			arr[place]=temp;
		}
		dp++;
	}
	return;
}

void QS(int start,int end){//快速排序函数
	if(start>=end){//排序完成，返回
		return;
	}
	else{
		if(end-start<5){//不足五，插排
			insert(start,end);
			return;
		}
		else{
			int place=sort(start,end);
			QS(start,place-1);
			QS(place+1,end);
			return;
		}
	}
}


int main(){
	//读入数据
	int num=0;
	char str[10]={0};
	gets(str);
	while(str[0]!='#'){
		arr[num]=StN(str);
		num++;
		gets(str);
	}
	QS(0,num-1);
	printf("After Sorting:\n");
	for(int i=0;i<num;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("Median3 Value:\n");
	if(mnum>0){
		for(int i=0;i<mnum;i++){
			printf("%d ",median[i]);
		}
		printf("\n");
	}
	else{
		printf("none\n");
	}
	return 0;
}