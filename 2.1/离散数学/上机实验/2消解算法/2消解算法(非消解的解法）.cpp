#include <bits/stdc++.h>
using namespace std;
#define max_size 2048
/*基本思路：
  1.使用1的现成程序，将获得的主合取式转化为逆波兰式
  2.依旧从头开始dfs，遇到成真赋值则min+1,遇到成假赋值则max+1
  3.最后看如果有成真赋值->可满足，否则即为矛盾式
*/

//全局变量域
char origin[max_size];//用来储存原串
int visit[max_size];//一个全局数组，用来记录某一个变量是否被访问(未访问未-1，访问后与赋值相同）
char RPN[max_size];//用来储存逆波兰式的数组

//记录极大项和极小项的
int bigone=0;
int smallone=0;

int var_value[max_size];//记录过程中变量赋值的数组
stack<int>num_stack;//dfs中记录数值内容的栈

//函数域
bool PriorityofOperator(char op1,char op2,int status){
/*处理运算符的函数--比较两运算符大小，
  前两个参数为两运算符，最后参数代表状态：置于status层括号内：括号内>0还是括号外=0
  如果op1比op2的运算级高则返回true,否则返回false；
  tips:除去括号的优先级：否定>合取析取>蕴含>等价
*/	 
    if(status>0){//此时在括号内->  !>&>|>->+>(>)
    	if(op1=='('){//栈顶运算符为（
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='+'){
				return false;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1==')'){//栈顶运算符为）
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='+'){
				return false;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return false;
			}
		}
		else if(op1=='!'){//栈顶运算符为！
    		if(op2=='!'){
    			return true;
			}
			else if(op2=='&'){
				return true;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='&'){//栈顶运算符为&
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return true;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='|'){//栈顶运算符为|
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='-'){//栈顶运算符为-
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return false;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='+'){//栈顶运算符为+
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
	}
	else{//此时在括号外-> (>)>!>&>|>->+
		if(op1=='('){//栈顶运算符为（
    		if(op2=='!'){
    			return true;
			}
			else if(op2=='&'){
				return true;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1==')'){//栈顶运算符为）
    		if(op2=='!'){
    			return true;
			}
			else if(op2=='&'){
				return true;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='!'){//栈顶运算符为！
    		if(op2=='!'){
    			return true;
			}
			else if(op2=='&'){
				return true;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return false;
			}
		}
		else if(op1=='&'){//栈顶运算符为&
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return true;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return false;
			}
		}
		else if(op1=='|'){//栈顶运算符为|
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return false;
			}
		}
		else if(op1=='-'){//栈顶运算符为-
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return false;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return false;
			}
		}
		else if(op1=='+'){//栈顶运算符为+
    		if(op2=='!'){
    			return false;
			}
			else if(op2=='&'){
				return false;
			}
			else if(op2=='|'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return false;
			}
		}
	}
}

int evalRPN(char origin[],int *varnum){//转换为逆波兰式函数
	int maxlenth=strlen(origin);//记录最大长度
	int lenth=0;//记录逆波兰式的长度
	int status=0;//记录括号内外状态的函数；
	std::stack<char> op;//储存符号的栈
	for(int i=0;i<maxlenth;i++){
		if(origin[i]>='a'&&origin[i]<='z'){//当前为变量,直接记录在新数组内
			RPN[lenth]=origin[i];
			lenth++;
		}
		else{//当前为符号
		    if(origin[i]=='('){//遇到左括号，直接放入栈顶
		    	op.push(origin[i]);
		    	status++;//更新状态
		    	continue;
			}
			else if(origin[i]==')'){//遇到右括号，直接将栈内直到它最近的那个左括号之间的进行弹出
				if(op.empty()!=true){//当栈内非空时
					char front;//记录栈顶元素
					while(op.empty()!=true){//当栈内非空时
					    front=op.top();
					    if(front=='('){//遇到左括号，直接退出
					    	break;
						}
						else{//非左括号则记录进RPN
						    RPN[lenth]=front;
						    lenth++;
						    op.pop();	
						}
					}
					if(op.empty()!=true){//在非空时退出，栈顶必为左括号,弹出一个左括号
						op.pop();
						status--;//更新状态
						continue;
					}
					else{//未找到匹配的左括号，出错了
						printf("ERROR1\n");
						continue;
					}
				}
				else{//当栈内为空时，出错了
					printf("ERROR2\n");
					continue;
				}
			}
			else{//对于其他情况
				if(op.empty()==true){//栈内为空，直接放
					op.push(origin[i]);
				}
				else{//栈内非空
					char front=op.top();
					if(PriorityofOperator(front,origin[i],status)==false){//栈顶优先级低，入栈
						op.push(origin[i]);
					}
					else{//栈顶优先级高，先弹出
						while(op.empty()!=true){//在栈内非空时
							front=op.top();
							if(PriorityofOperator(front,origin[i],status)==false){//直到栈顶优先级低为止
								break;
							}
							else{
								RPN[lenth]=front;
								lenth++;
								op.pop();
								continue;
							}
						}
						op.push(origin[i]);
					}
				}
			}
		}
	}
	//当所有字符被遍历后，就可以直接将栈内内容一个个弹出来了
	while(op.empty()!=true){
		char front=op.top();
		RPN[lenth]=front;
		lenth++;
		op.pop();
	}
	//加个结束标识符
	RPN[lenth]='#';
	lenth++;
	return lenth;
}

int dual_cal(int num1,int num2,char op){//双目运算区
	if(op=='&'){
		if(num1==1&&num2==1){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(op=='|'){
		if(num1==1||num2==1){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(op=='-'){
		if(num1==1&&num2==0){
			return 0;
		}
		else{
			return 1;
		}
	}
	else if(op=='+'){
		if(num1==num2){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		printf("dual ERROR\n");
		return -1;
	}
}

int sing_cal(int num1,char op){//单目预算区
	if(op=='!'){
		if(num1==0){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		printf("sing ERROR\n");
		return -1;
	}
}

void dfs(int cur,int cur_var){//cur指向当前位置，cur_var记录已被赋值的变量个数
	if(RPN[cur]=='#'){//到了底了
		int final_result=num_stack.top();
		if(final_result==0){//成假，为一极大项
		    bigone++;
		    return;		
		}
		else if(final_result==1){//成真，为一极小项
		    smallone++;
		    return ;
		}
		else{
			printf("no 0 no 1 ERROR\n");
			return ;
		}
	}
	else if(RPN[cur]>='a'&&RPN[cur]<='z'){//当前为一个变量
	    if(visit[RPN[cur]-97]!=-1){//已经被赋值了
	    	num_stack.push(visit[RPN[cur]-97]);
	    	dfs(cur+1,cur_var);//递归到下一层
	    	num_stack.pop();//将影响消除
	    	return;
		}
		else{//未被访问过
		    //先设置该变量为0
		    var_value[cur_var]=0;
			visit[RPN[cur]-97]=0;
			num_stack.push(visit[RPN[cur]-97]);
			dfs(cur+1,cur_var+1);
			num_stack.pop();
			//再设置为1
			var_value[cur_var]=1;
			visit[RPN[cur]-97]=1;
			num_stack.push(visit[RPN[cur]-97]);
			dfs(cur+1,cur_var+1);
			//清楚影响，返回
			visit[RPN[cur]-97]=-1;
			num_stack.pop();
			return;
		}
	}
	else{//当前为一个非结束的符号
		if(RPN[cur]=='!'){//为一个单目的
			int num1=num_stack.top();
			int result=sing_cal(num1,RPN[cur]);
			num_stack.pop();
			num_stack.push(result);
			dfs(cur+1,cur_var);
			//消除影响返回
			num_stack.pop();
			num_stack.push(num1);
			return ;
		}
		else{//为一双目的
			int num2=num_stack.top();
			num_stack.pop();
			int num1=num_stack.top();
			int result=dual_cal(num1,num2,RPN[cur]);
			num_stack.pop();
			num_stack.push(result);
			dfs(cur+1,cur_var);
			//消除影响返回
			num_stack.pop();
			num_stack.push(num1);
			num_stack.push(num2);
			return ;
		}	
	}
	
}

int main(){
	//part 1:前置条件，读入原始合式
	memset(origin,0,sizeof(origin));
	gets(origin);//读入origin
	memset(RPN,0,sizeof(RPN));//将逆波兰式数组重置
	
	
	//part2:转换为逆波兰式,记录可能的变量个数
	int varnum=0;//记录变量个数
	int RPNlenth=0;//记录逆波兰式的长度，最后跟标识符#
	RPNlenth=evalRPN(origin,&varnum);
	
	//part3:从第一个变量开始，进行dfs
	memset(visit,-1,sizeof(visit));//将全局数组visit重置
	dfs(0,0);
	
	//part4:输出结果
	if(smallone>0){//有成真赋值，可满足
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}
}