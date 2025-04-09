#include <bits/stdc++.h>

/*
思路：
按开始时间由早到晚进行排序，
当一个活动安排不进当前任意一个教室时，
重新开一间教室安排

注：
由于数据量比较大，本题采用快读模板对数据的读写速度进行提升
*/


//全局变量域
#define maxsize 1000005
typedef struct{
	int s;//开始时间
	int e;//结束时间
}event;

event acl[maxsize];//记录事件起止时间
int usable[maxsize];//记录某个房间空闲的时间

//全局函数域
inline void read(int& n){
	n=0;
	char ch=getchar();
	while(ch<='9'&&ch>='0'){//是数字
		n=n*10+(ch-48);
		ch=getchar();
	}
	return;
}

bool compare(event a,event b){//按结束时间升序排布
	return a.s<b.s;
}

int main(){
	memset(usable,-1,sizeof(usable));
	int room=0;//峰值房间数
	int num=0;//总的活动数
	read(num);
	for(int i=0;i<num;i++){
		read(acl[i].s),read(acl[i].e);
	}
	std::sort(acl,acl+num,compare);//按开始时间升序排序
	
	
	//先将第一个放入
	usable[room]=acl[0].e;
	room++;
	//对后续活动进行遍历
	for(int i=1;i<num;i++){
		int place=0;
		for(;place<room;place++){//在已经开辟的房间里找能用的
			if(usable[place]<=acl[i].s){//找到一个空房间
				break;
			}
			else{
				continue;
			}
		}
		if(place<room){
			usable[place]=acl[i].e;
			continue;
		}
		else{
			usable[room]=acl[i].e;
			room++;
			continue;
		}
	}
	printf("%d\n",room);
	return 0;	
}