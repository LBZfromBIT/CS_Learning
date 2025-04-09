/*基本思路：猛的一看，两两交换，大数逐渐向后摆，基本就是冒泡排序算法的模型了
            但由于数据量比较大，冒泡的O(n^2)的时间复杂度会导致TLE
            该换方法了：化整为零，利用归并排序的方法，在过程中记录出现交换的次数（即逆序数）
            而逆序数即对应了冒泡中使用的最小步数
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int high[400000]={0};
long long int sum=0;//最后的和
void together(long long int a[],int begin1,int end1,int begin2,int end2) {//合并函数，begin1，end1两个参数指向左侧右侧同理
	if(a==NULL||begin1>end1||begin2>end2||end1>begin2){//极端情况直接返回
		return;
	}
	else{
	    int lenth=end2-begin1+1;//拼接后总长
	    long long int *temp=(long long int *)malloc(sizeof(long long int)*lenth);//开一个暂存数组，储存合并后的字符串
	    int i=begin1,j=begin2,k=0;//i在左侧遍历，j在右侧遍历，k在新数组内遍历
	    while(i<=end1&&j<=end2){//在共有长度内
		    if(a[i]<=a[j]){//这取小于等于，防止相等情况被看作逆序
			    temp[k]=a[i];
			    k++;
			    i++;
		    }
		    else{
			    temp[k]=a[j];
			    k++;
			    j++;
			    sum+=begin2-i;
		    }
	    }
	    //接下来，把各自部份内没跑完的跑进去
	    while(i<=end1){
		    temp[k]=a[i];
		    k++;
		    i++;
	    }
	    while(j<=end2){
		    temp[k]=a[j];
		    k++;
		    j++;
	    }
	    for(int acur=begin1,tcur=0;acur<=end2;acur++,tcur++){//把暂存的数组写入原数组对应位置
		    a[acur]=temp[tcur];
	    }
	    free(temp);//释放空间
        temp=NULL;//指针置空
        return;
	}
	
}

void sort(long long int a[],int begin,int end){//递归排序函数
    if(a==NULL||begin>=end){//极端情况和只有一个元素直接返回
    	return;
	}
	else{
	    int mid=(begin+end)/2;//中断点：mid,为从开头指针向后移动一半
	    sort(a,begin,mid);//中断点左侧二分
	    sort(a,mid+1,end);//中断点右侧二分
	    together(a,begin,mid,mid+1,end);//最后合并
	    return;
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		if(i==n){
			scanf("%lld",&high[i]);
		}
		else{
			scanf("%lld ",&high[i]);
		}
	}

	sort(high,1,n);
	printf("%lld\n",sum);
}
