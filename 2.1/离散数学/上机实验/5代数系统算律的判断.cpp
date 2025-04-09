#include <bits/stdc++.h>
using namespace std;

/*
基本思路：
检查元素：若为字母的，对应数字；使用二维表储存运算表
1.交换律
按定义，a[i][j]=a[j][i]
2.幂等律
按定义，a[i][i]=i
3.结合律
按定义，a[(a[i][j])][k]=a[i][(a[j][k])]
4.幺元
按定义，存在元素i，使得第i行与第i列都为另一个元素
5.零元
按定义，存在元素i，使得第i行与第i列都为i
*/

//全局变量域
#define M 128
int data[M][M];//储存运算表
int trans[M];//用来将字符转化为数字的映射表


//全局函数域
void isCommutative(int num){//交换律
    for(int i=0;i<num;i++){
        for(int j=i+1;j<num;j++){
            if(data[i][j]!=data[j][i]){
                printf("commutative law:n\n");
                return;
            }
        }
    }
    printf("commutative law:y\n");
    return;
}

void isAssociative(int num){//结合律
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            for(int k=0;k<num;k++){
                if(data[data[i][j]][k]!=data[i][data[j][k]]){
                    printf("associative law:n\n");
                    return;
                }
            }
        }
    }
    printf("associative law:y\n");
    return;
}

void isIdempotent(int num){//幂等律
    for(int i=0;i<num;i++){
        if(data[i][i]!=i){
            printf("idempotent law:n\n");
            return;
        }
    }
    printf("idempotent law:y\n");
    return;
}

void identity(int num){//幺元
    for(int i=0;i<num;i++){
        bool status=true;
        for(int j=0;j<num;j++){
            if(data[i][j]!=j||data[j][i]!=j){
                status=false;
                break;
            }
        }
        if(status==true){
            char ch='0';
            for(int t=0;t<M;t++){
                if(trans[t]==i){
                    ch=(char)t;
                    break;
                }
            }
            printf("identity element:%c\n",ch);
            return;
        }
    } 
    printf("identity element:n\n");
}

void zero(int num){//零元
    for(int i=0;i<num;i++){
        bool status=true;
        for(int j=0;j<num;j++){
            if(data[i][j]!=i||data[j][i]!=i){
                status=false;
                break;
            }
        }
        if(status==true){
            char ch='0';
            for(int t=0;t<M;t++){
                if(trans[t]==i){
                    ch=(char)t;
                    break;
                }
            }
            printf("zero element:%c\n",ch);
            return;
        }
    } 
    printf("zero element:n\n");
}

int main(){
	memset(data,-1,sizeof(data));
    memset(trans,-1,sizeof(trans));
    int num=0;
    scanf("%d",&num);
    getchar();
    char ch='0';
    for(int i=0;i<num;i++){
        scanf("%c",&ch);
        trans[(int)ch]=i;//按录入顺序构建映射
        getchar();
    }

    //录入运算表
    for(int row=0;row<num;row++){
        for(int col=0;col<num;col++){
            scanf("%c",&ch);
            data[row][col]=trans[(int)ch];
            getchar();
        }
    }

    //接下来使用函数；
    isCommutative(num);
    isAssociative(num);
    isIdempotent(num);
    identity(num);
    zero(num);
    return 0;
}