#include <bits/stdc++.h>
#define max_size 1000

/*基本思路：
  1.利用三元组表的方式储存非零元素
  2.利用乘法定义去计算矩阵乘法，只有最后的元素不为零才记录到最后的新三元组里
  */

//全局变量域
typedef struct{
	int row,col,value;//行，列，值
}tri_element;//三元表元素

typedef struct{
	tri_element array[max_size];//三元表组
	int place[max_size];//行索引数组
	int Row,Column,Number;//矩阵的行，列，非零个数
}tri_table;
tri_table M,N,ans;//M，N为计算矩阵，ans为结果矩阵

//函数域
void init(tri_table *a){//初始化函数
	a->Row=0;
	a->Column=0;
	a->Number=0;
	memset(a->array,0,sizeof(a->array));
	memset(a->place,0,sizeof(a->place));
	return ;
}

void oset(tri_table *a){//读入数据函数
	scanf("%d%d%d",&(a->Row),&(a->Column),&(a->Number));
	for(int i=1;i<=a->Number;i++){//记录元素
		scanf("%d%d%d",&(a->array[i].row),&(a->array[i].col),&(a->array[i].value));
		//记录数据后开始完善行索引表
		if(a->place[a->array[i].row]==0){//为该行的首个非零元素
			a->place[a->array[i].row]=i;//将三元组中的位置写入行索引
		}
	}
	return ;
}

int main(){
	//初始化并读入数据
	init(&M);
	init(&N);
	oset(&M);
	oset(&N);
	//处理结果函数
	init(&ans);
	ans.Row=M.Row;
	ans.Column=N.Column;
	ans.Number=0;
	//开始计算当前元素位置是否为0
	/*
			算法思路：
			积矩阵中A(i,j)=对k求和[（M的i行k列元素）*（N的k行j列元素）]
			又由于过程中只考虑非零元
			因此
			先由行出发，获得M的第i行的第一个非零元（前提：M的第i行有非零元素），获得其列k和值value
			在k不超限的情况下（N的第k行应该有非零元素），遍历N的第k行非零元素，寻找是否有列为j的，进行运算后求和
			在和不为0的情况下，将其写入答案矩阵的三元组
	*/
	for(int i=1;i<=ans.Row;i++){
		for(int j=1;j<=ans.Column;j++){
			int sum=0;//记录求和的计数器
			if(M.place[i]==0){//超限，继续循环
				continue;
			}
			else{
				int Mnext;
				if(M.place[i+1]==0){//i+1行没非零元->从第i+2行找下一个有变元的行
				    int back; 
				    bool tag=false;
					for(back=i+2;back<=M.Row;back++){
						if(M.place[back]!=0){//遇到有变元的
						    tag=true;
							break;
						}
					}
					if(tag==true){//后面还有行有变元
						Mnext=M.place[back];
					}
					else{//否则直接指向三元组表尾
						Mnext=M.Number+1;
					}
				}
				else{
					Mnext=M.place[i+1];
				}
				for(int Mthis=M.place[i];Mthis<Mnext;Mthis++){
					int k=M.array[Mthis].col;
					int op1=M.array[Mthis].value;
					//匹配N去
					if(N.place[k]==0){
						continue;
					}
					else{
						int Nnext;
						if(N.place[k+1]==0){
							int Nback;
							bool found=false;
							for(Nback=k+2;Nback<=N.Row;Nback++){
								if(N.place[Nback]!=0){
									found=true;
									break;
								}
							}
							if(found==true){
								Nnext=N.place[Nback];
							}
							else{
								Nnext=N.Number+1;
							}
						}
						else{
							Nnext=N.place[k+1];
						}
						for(int Nthis=N.place[k];Nthis<Nnext;Nthis++){
							if(N.array[Nthis].col==j){
								int op2=N.array[Nthis].value;
								sum+=op1*op2;
								break;
							}
						}
					}
				}
			}
			if(sum!=0){//和不为零，写入三元组
				ans.Number++;
				ans.array[ans.Number].row=i;
				ans.array[ans.Number].col=j;
				ans.array[ans.Number].value=sum;
			}
		}
	}
	//输出结果
	printf("%d\n%d\n%d\n",ans.Row,ans.Column,ans.Number);
	for(int i=1;i<=ans.Number;i++){
		printf("%d,%d,%d\n",ans.array[i].row,ans.array[i].col,ans.array[i].value);
	}
	return 0;
}