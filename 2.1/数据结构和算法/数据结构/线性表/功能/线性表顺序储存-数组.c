#include <stdio.h>
#include <stdlib.h>


// 对于一个顺序储存的线性链表（以一维数组为例），有如下基本定义： 
#define MAXSIZE 20//表征该数组的长度（最大储存空间）
typedef int ElmeType;//表征该数组内数据元素的类型为整型
typedef struct { //定义一种结构体，对应该线性表（包含两个数据项，储存数组和线性表长度）
	ElmeType data[MAXSIZE];//该整形数组为数据元素的储存位置
        int length;//记录该线性表的长度
}SqList;

//可以有如下的操作：
//1.在线性表L中定位与给定值e相等的元素，返回其位置i
#define OK 1//函数正确执行时返回1
#define ERROR 0//考虑到函数的健壮性，当函数出现错误时，返回0
typedef int STATUS;//STATUS为整型，对应上述返回值
STATUS LocateElme(SqList L,ElmeType e, int *i){
	if(L.length==0){//若线性表为空
		return ERROR;
	}
	else{//线性表非空时遍历线性表，找到对应元素停止
		for(int k=0;k<L.length;k++){
			if(e==L.data[k]){
                           *i=k;
			   return OK;
			}
		}
	        return ERROR;	//没找到就返回错误
	}
}	  

//2.获得某位置上的数据元素操作(L线性表中的第i个，其值赋给e)
STATUS GetELme(SqList L,int i,int *e){//定义GetELme函数(此处参数e被改变，使用指针传递)
	if (i<1 || i>L.length || L.length==0){//当i不在线性表中时或线性表没有数据元素时
             return ERROR;
	}
	else{//当i在线性表中时，正常返回1，并将第i个数据元素的指针给到e
             *e=L.data[i-1];
	     return OK;
	}
}		   

//3.在线性表的指定位置插入一个元素（L线性表的第i位插入e，其他元素不应改变顺序）
STATUS ListInsert (SqList *L,int i,ElmeType e){//定义ListInsert函数（此处线性表被改变，使用指针传递）
	if(i<1 || i>L->length+1){//i不在该线性表中，且不在队尾，返回0
             return ERROR;
	}
	else if(i==L->length+1){//当i在队尾时，直接在线性表后面加上该数据，线性表长度加1
	     L->data[i-1]=e;
	     L->length++;
             return OK;
	}
	else{//当i在队列中时，位于第i个后面（包含第i位）统一向后挪一位（使用倒叙循环更方便），在第i位插入数据，线性表长度加1
		for(int k=L->length;k>=i;k--){
			L->data[k]=L->data[k-1];
		}
		L->data[i-1]=e;
		L->length++;
		return OK;
	}
}

//4.在线性表的指定位置删除一个元素（L线性表的第i位元素删除，其值给到e）
STATUS ListDelete(SqList *L,int i,ElmeType *e){
	if(i<1 || i>L->length || L->length==0){//如果i不在线性表当中或者线性表为空，返回0
		return ERROR;
	}
	else{//当i在线性表中时，将第i位元素提取到e，然后从第i位开始将之后的元素向前移动，线性表长度减1
		*e=L->data[i-1];
		for(int k=i-1;k<L->length-1;k++){//注意是将倒数第一个转到倒数第二个，所以边界条件为k<L->length-1
			L->data[k]=L->data[k+1];
		}
		L->length--;
	}
}


