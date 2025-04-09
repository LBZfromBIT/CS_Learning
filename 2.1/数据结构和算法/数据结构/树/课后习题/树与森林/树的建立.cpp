#include <bits/stdc++.h>
using namespace std;

/*基本思路：
   https://blog.csdn.net/qq_41680771/article/details/121032256
   //把他完全当做一串字符来处理
*/

//按照格式打印节点
void print(char c[],int level[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<level[i];j++)
            cout<<"    ";
        cout<<c[i]<<endl;
    } 
	return;   
}
int bigger(int a,int b){//比较大值
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}


int main(){
    char ch[100]={0};         //储存字符
    int maxdegree=0;        //最大的度
    int i,j;
    int num=0;  //下标
    int level[100]; //和ch的下标对应，意义是ch[i]这个字符位于第几层（depth）
    int depth=-1;           
 
    
    char c;
    c=getchar();  //读取字符
    while(c!='\n'){
        switch(c){
            case '(':depth++;break;
            case ')':depth--;break;
            case ',':break; //只存字母，其他的都不要
            case ' ':break; 
            default:
                ch[num]=c;  //存入当前字符
                level[num]=depth; //刚刚存入字符位于第几层
                num++;//num++
                break;    
        }
        c=getchar();
    }
    print(ch,level,num);  
	
	int degree[100]={0};    
    for(i=0;i<num-1;i++){       
        for(j=i+1;j<num;j++){
            if(level[j]==level[i])      //说明遇到了和i同一层的j了，这时候应该跳过这个i了，开始下轮，因为之后的位于i+1层（下一层）的已经不是i的子节点了，是j的子节点
                break;
            if(level[i]+1==level[j])        //说明j是i的下一层，那么i这个位置的度+1
                degree[i]++;            
        }
        maxdegree=bigger(maxdegree,degree[i]);  
    }
    cout<<"Degree of tree: "<<maxdegree<<endl;
    
    int counts[100]={0};
    for(i=0;i<num;i++){
        counts[degree[i]]++;       
    }
    for(i=0;i<=maxdegree;i++){     //maxdegree已经是最大的了
        cout<<"Number of nodes of degree "<<i<<": "<<counts[i]<<endl;
    }
    return 0;
}
