#include <bits/stdc++.h>
#define max_size 100

//全局变量域
int TLO;//飞机降落耗时
int TFO;//飞机起飞耗时
int RN;//跑道数量
int LO;//降落飞机编号
int FO;//起飞飞机编号

typedef struct{
	int NO;//编号
	int wait_time;//已经等待的时间（每分钟更新，直到分配跑道出队列）
}plane;//飞机结构体
std::queue <plane> land;//降落队列
std::queue <plane> fly;//起飞队列

typedef struct{
	int NO;//编号
	bool status;//占用状态（可用为true，不可用为false，每分钟更新)
	int rest;//当前架次剩余占用时间（为0时即为free，每分钟更新)
	int total;//总计被占用时间，每架飞机进入时更新
}line;//跑道
line race[max_size];//跑道数组
std::queue <int> record;//记录跑道可用状态的队列

int sumtime;//计时器
bool tag;//是否关闭标签（关闭为false;开放为true)
int LR;//降落飞机请求数
int FR;//起飞飞机请求数
int TL;//总降落数
int TF;//总起飞数
int TLW;//总的降落等待时间（降落队列出飞机时更新）
int TFW;//总的起飞等待时间（起飞队列出飞机时更新）

//函数域
//1.初始化函数
void init(){
	sumtime=0;//时间重置
	tag=true;//标签重置
	FO=1;//起飞编号重置
	LO=5001;//降落编号重置
	
	//构建跑道信息
	while(record.empty()!=true){
		record.pop();
	}
	for(int i=1;i<=RN;i++){
		race[i].NO=i;//写入编号
		race[i].status=true;//写入状态
		race[i].rest=0;//剩余时间重置
		race[i].total=0;//总计被占用时间重置
		record.push(race[i].NO);//计入跑道队列
	}
	
	//清空飞机队列
	while(land.empty()!=true){
		land.pop();
	}
	while(fly.empty()!=true){
		fly.pop();
	}
	return;
}

//2.判断模拟终止函数
bool finish(){
	if(tag==true){//机场开放
		return false;
	}
	else{//机场关闭了
		//判断起飞和降落队列是否为空
		if(land.empty()!=true||fly.empty()!=true){//不为空
			return false;
		}
		else{
			/*
			//判断各跑道是否为空
			for(int i=1;i<=RN;i++){
				if(race[i].status==false){//有跑道被占用
					return false;
				}
				else{
					continue;
				}
			}
			return true;//全部结束
			*/
			if(record.size()==RN){
				return true;
			}
			else{
				return false;
			}
		}
	}
}

//3.更新跑道状态函数
void update_line(){
	for(int i=1;i<=RN;i++){
		if(race[i].status==true){//早已可用，跑道信息必然早已在队列中
			continue;
		}
		else{
			race[i].rest--;
			if(race[i].rest==0){//恢复可用,将跑道信息放入队列待用
				race[i].status==true;
				record.push(race[i].NO);
				printf("runway %02d is free\n",race[i].NO);
			}
		}
	}
	return;
}

//4.更新飞机状态函数
void update_plane(){
	//1.先看是否有新的飞机需要写入
	if(tag==true){//tag为真，有新的请求
		//先写入降落
		for(int i=1;i<=LR;i++){
			plane lp;
			lp.NO=LO;
			lp.wait_time=0;
			land.push(lp);
			LO++;
		}
		//再写入起飞
		for(int i=1;i<=FR;i++){
			plane fp;
			fp.NO=FO;
			fp.wait_time=0;
			fly.push(fp);
			FO++;
		}
	}
	//2.再进行跑道和飞机的配对（先降落后起飞、队列之内先来后到的顺序）
	//先看当前是否有可用跑道
	if(record.empty()!=true){//有可用跑道
		//优先给降落飞机使用
		while(record.empty()!=true&&land.empty()!=true){//有待降落飞机
			plane lp=land.front();//队首
			int runway=record.front();
			//当前飞机进跑道
			race[runway].status=false;
			race[runway].rest=TLO;
			race[runway].total+=TLO;
			//显示匹配信息
			printf("airplane %04d is ready to land on runway %02d\n",lp.NO,race[runway].NO);
			TLW+=lp.wait_time;
			//两参量弹出
			record.pop();
			land.pop();
		}
		//在还有跑道并且还有起飞飞机时
		while(record.empty()!=true&&fly.empty()!=true){
			plane fp=fly.front();//队首
			int runway=record.front();
			//当前飞机进跑道
			race[runway].status=false;
			race[runway].rest=TFO;
			race[runway].total+=TFO;
			//显示匹配信息
			printf("airplane %04d is ready to takeoff on runway %02d\n",fp.NO,race[runway].NO);
			TFW+=fp.wait_time;
			//两参量弹出
			record.pop();
			fly.pop();
		}
	}
	//3.再对队伍中继续等待的飞机等待时间进行更新
	//此处，由于队列的FIFO特性，无法遍历，只能front->pop->push
	//先处理降落队列
	int lsize=land.size();
	for(int i=1;i<=lsize;i++){
		plane lp=land.front();
		lp.wait_time++;
		land.push(lp);
		land.pop();
	}
	//再处理起飞队列
	int fsize=fly.size();
	for(int i=1;i<=fsize;i++){
		plane fp=fly.front();
		fp.wait_time++;
		fly.push(fp);
		fly.pop();
	}
	return;
}

int main(){
	//录入基本信息，并初始化
	scanf("%d %d %d",&RN,&TLO,&TFO);
	init();
	
	//开始模拟
	while(finish()!=true){//模拟不终止时
	    //输出时间
		printf("Current Time: %4d\n",sumtime);
		//更新跑道状态并列出释放的跑道
		update_line();
		//还开启时获取该分钟得到的请求
		if(tag==true){
			scanf("%d %d",&LR,&FR);
			if(LR<0&&FR<0){//机场关闭
				tag=false;
			}
			else{
				TL+=LR;
				TF+=FR;
			}
		}
		//处理飞机队列
		update_plane();
		//时间更新
		sumtime++;
	}
	printf("simulation finished\n");
	//处理数据
	sumtime--;//减去多的
	printf("simulation time: %4d\n",sumtime);
	printf("average waiting time of landing: %4.1f\n",((float)TLW)/TL);
	printf("average waiting time of takeoff: %4.1f\n",((float)TFW)/TF);
	float sum=0;
	for(int i=1;i<=RN;i++){
		printf("runway %02d busy time: %4d\n",race[i].NO,race[i].total);
		sum+=(float)race[i].total;
	}
	float final=((sum/RN)*100)/sumtime;
	printf("runway average busy time percentage: %4.1f%%\n",final);
}