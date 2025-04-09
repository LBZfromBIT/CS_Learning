#include <bits/stdc++.h>
#define max_size 2048
#define alphabet 30
/*基本思路（消解思路）：
   1.先拿到原始的主合取式后，将其拆分为各个析取式(用二维表记录）然后进队储存
   2.然后从队中第一个开始向后循环，每次循环中向后取，判断是否能够获得消解式
     不能就继续，能得就把消解式进队并且记录新式子加1
   3.如果遇到了空式子->不可满足，直接退出返回status=false,
     如果新式子=0，意味着所有可能的式子都已得出，则返回true
   4.输出结果
*/

//全局变量域
char origin[max_size];//存储原始数据的数组

typedef struct{//存储析取式信息的结构体
	int table[alphabet];//储存变量信息的数组，数组下标对应为（变量名-97），值对应变量的状态（-1没有，0为!p，1为p）
	int num=0;//记录变量个数
}cal_part;
cal_part old_array[max_size];//程序中进行堆叠的数组
cal_part new_array[max_size];//程序中进行堆叠的数组


int init(char origin[],cal_part array[]){//构建函数
    int arraynum=0;
	for(char *p=strtok(origin,"&");p!=NULL;p=strtok(NULL,"&")){
		if(p[0]!='\n'){//截取到了有效内容
		    //初始化
			memset(array[arraynum].table,-1,sizeof(array[arraynum].table));
			array[arraynum].num=0;
			//开始进行处理
			int lenth=strlen(p);
			for(int i=0;i<lenth;i++){
				if(p[i]>='a'&&p[i]<='z'){//是个变量
					array[arraynum].num++;//计数先加一
					if(i>0&&p[i-1]=='!'){//为！p时
						array[arraynum].table[p[i]-97]=0;
					}
					else{//为p时
						array[arraynum].table[p[i]-97]=1;
					}
				}
				else{//是个符号
					continue;
				}
			}
			//收尾
			arraynum++;
		}
		else{//截到最后的换行了
			continue;
		}
	}
	return arraynum;
}

bool same(cal_part a,cal_part b){//判断两个式子是否一样
	if(a.num!=b.num){
		return false;
	}
	else{
		bool dif=false;
		for(int i=0;i<alphabet;i++){
			if(a.table[i]!=b.table[i]){
				dif=true;
				break;
			}
		}
		if(dif==false){
			return true;
		}
		else{
			return false;
		}
	}
}

int cal(cal_part a,cal_part b,int old_number,int new_number){//消解的函数(消解成功返回1，不成功返回0，出现空式子返回-1）
    bool status=false;//消解状态（true为进入消解态，fasle为非消解态）
    //先判断两个是不是可以消解（出现一个变元反着）
	for(int i=0;i<alphabet;i++){
		if(a.table[i]==0&&b.table[i]==1){
			a.table[i]=-1;
			b.table[i]=-1;
			a.num--;
			b.num--;
			status=true;
			break;
		}
		else if(a.table[i]==1&&b.table[i]==0){
			a.table[i]=-1;
			b.table[i]=-1;
			a.num--;
			b.num--;
			status=true;
			break;
		}
		else{
			continue;
		}
	}
	//如果不可以消解
	if(status==false){
		return 0;
	}
	else{//如果可以消解
		for(int i=0;i<alphabet;i++){
			if(a.table[i]!=-1||b.table[i]!=-1){//有效变元出现
				new_array[new_number].num++;
				if(a.table[i]==b.table[i]){//两个变元相同
					new_array[new_number].table[i]=a.table[i];
				}
				else if(a.table[i]==-1){//a没有
					new_array[new_number].table[i]=b.table[i];
				}
				else if(b.table[i]==-1){//b没有
					new_array[new_number].table[i]=a.table[i];
				}
				else{//同一个变元互补,该析取式将化为1，无效消解，将进队重置
				    memset(new_array[new_number].table,-1,sizeof(new_array[new_number].table));
	                new_array[new_number].num=0;
					return 0;
				}
			}
			else{//变元未出现
				continue;
			}
		}
		//消解完成，判断重复和空式
		if(new_array[new_number].num==0){//空式子,重置返回-1
		    memset(new_array[new_number].table,-1,sizeof(new_array[new_number].table));
	        new_array[new_number].num=0;
			return -1;
		}
		else{
			bool repeat=false;
			for(int i=0;i<old_number;i++){//验重复
				if(same(new_array[new_number],old_array[i])==true){
					repeat=true;
					break;
				}
			}
			if(repeat==false){//没重
				return 1;
			}
			else{//重了
				memset(new_array[new_number].table,-1,sizeof(new_array[new_number].table));
	            new_array[new_number].num=0;
				return 0;
			}
		}
	}
	
}

//主函数区域
int main(){
	//1.初始化,获得原始式子及式子中存在的变量个数
	memset(origin,0,sizeof(origin));
	gets(origin);
	
	//2.拆分主合取式，获得各部分，并且构建队
	int old_number=init(origin,old_array);//记录队伍中有多少析取式
	
	//3.队伍构建完毕，开始循环
	int new_number=0;
	do{
		if(new_number!=0){//new_array里有析取式，把其中所有的都放入old_array里
			for(int i=0;i<new_number;i++){
				old_array[old_number]=new_array[i];
				memset(new_array[i].table,-1,sizeof(new_array[i].table));
				new_array[i].num=0;
				old_number++;
			}
			new_number=0;
		}
		for(int i=0;i<old_number-1;i++){
			for(int j=i+1;j<old_number;j++){
				int status=cal(old_array[i],old_array[j],old_number,new_number);
				if(status==0){//未出现新的析取式
					continue;
				}
				else if(status==-1){//出现空式子
					printf("NO\n");
					return 0;
				}
				else{//出现了新的析取式且非空式
					new_number++;
				}
				
			}
		}
	}while(new_number!=0);//跳出条件，不再产生新的析取式
	
	printf("YES\n");
	return 0;
	
}