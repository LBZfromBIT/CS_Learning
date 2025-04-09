#include <bits/stdc++.h>
#define max_size 1000

//全局变量区
std::stack <int> num_stack;//数字栈
std::stack <char> op_stack;//符号栈
char word[max_size];//存算式数组
bool tag;//正负标识,正数为true,负数为false
int status;//记录括号内外的参量

//函数区
int type(char a){
	//判断类型的函数，数字返回1，符号返回0
	if(a>='0'&&a<='9'){
		return 1;
	}
	else{
		return 0;
	}
}

bool N(char word[],int place){
	//判断当前减号是不是负号：是返回true；不是返回false
	if(type(word[place+1])==1){//只有当其后面紧跟数字，才可能是负号
		if(place==0||type(word[place-1])==0){//要么前面没有内容，要么前面也是符号
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool P(char word[],int place){
	//判断当前加号是不是正号：是返回true；不是返回false
	if(type(word[place+1])==1){//只有当其后面紧跟数字，才可能是正号
		if(place==0||type(word[place-1])==0){//要么前面没有内容，要么前面也是符号
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

int gather(char word[],int place1,int place2,bool tag){
	//用来将char型数字改为int型数字
	//其中place1为开头数位位置，place2为结束数位位置，tag表示是否为负数
	int range=1;//数位乘数
	int sum=0;//和
	for(int i=place2;i>=place1;i--){
		sum+=(word[i]-48)*range;
		range=range*10;
	}
	if(tag==true){//为正数
		return sum;
	}
	else{//负数
		return 0-sum;
	}
}

bool compare(char op1,char op2,int status){
	//优先级比较函数，op1,op2为两个运算符，status为tag
    //实现效果：当op1的优先级高于op2时，返回true;否则返回false；
	if(status>0){//在括号内
		if(op1=='^'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
				return true;
			}
			else if(op2=='%'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='*'||op1=='/'||op1=='%'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
				return true;
			}
			else if(op2=='%'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='+'||op1=='-'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return false;
			}
			else if(op2=='/'){
				return false;
			}
			else if(op2=='%'){
				return false;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='('){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return false;
			}
			else if(op2=='/'){
				return false;
			}
			else if(op2=='%'){
				return false;
			}
			else if(op2=='+'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1==')'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return false;
			}
			else if(op2=='/'){
				return false;
			}
			else if(op2=='%'){
				return false;
			}
			else if(op2=='+'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
	}
	else{//在括号外
		if(op1=='^'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
				return true;
			}
			else if(op2=='%'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='*'||op1=='/'||op1=='%'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
				return true;
			}
			else if(op2=='%'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='+'||op1=='-'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return false;
			}
			else if(op2=='/'){
				return false;
			}
			else if(op2=='%'){
				return false;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1=='('){
			if(op2=='^'){
				return true;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
				return true;
			}
			else if(op2=='%'){
				return true;
			}
			else if(op2=='+'){
				return true;
			}
			else if(op2=='-'){
				return true;
			}
			else if(op2=='('){
				return true;
			}
			else if(op2==')'){
				return true;
			}
		}
		else if(op1==')'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return false;
			}
			else if(op2=='/'){
				return false;
			}
			else if(op2=='%'){
				return false;
			}
			else if(op2=='+'){
				return false;
			}
			else if(op2=='-'){
				return false;
			}
			else if(op2=='('){
				return false;
			}
			else if(op2==')'){
				return true;
			}
		}
	}
}

bool legal(int num1,int num2,char op){
	//判断运算过程中是否合法的函数：合法返回true，非法返回false
	if(op=='^'){//指数非负
		if(num2<0){
			return false;
		}
		else{
			return true;
		}
	}
	else if(op=='/'||op=='%'){//除数不为零
		if(num2==0){
			return false;
		}
		else{
			return true;
		}
	}
	else if(op!='^'&&op!='*'&&op!='/'&&op!='%'&&op!='+'&&op!='-'){//出现非运算符
		return false;
	}
	else{
		return true;
	}
}

int cal(int num1,int num2,char op){
	//计算得数的函数
	int result=0;//最终返回值
	if(op=='^'){
		if(num2==0){
			result=1;
		}
		else{
			for(int time=1;time<=num2;time++){
			    if(time==1){
				    result=num1;
				    continue;
			    }
			    else{
				    result=result*num1;
				    continue;
			    }
		    }	
	    }
    }
	else if(op=='*'){
		result=num1*num2;
	}
	else if(op=='/'){
		result=num1/num2;
	}
	else if(op=='%'){
		result=num1%num2;
	}
	else if(op=='+'){
		return num1+num2;
	}
	else if(op=='-'){
		result=num1-num2;
	}
	return result;
}

bool SBC(char word[]){
	//初始检查函数->判断括号是否合法；合法返回true;非法返回false;
	int num=strlen(word);
	int lbra=0;
	for(int i=0;i<num;i++){
		if(word[i]!='('&&word[i]!=')'){
			continue;
		}
		else{
			if(word[i]=='('){//左括号进栈
				lbra++;
				continue;
			}
			else{//右括号判断
				if(lbra>0){
					lbra--;
					continue;
				}
				else{
					return false;
				}
			}
		}
	}
	if(lbra==0){
		return true;
	}
	else{
		return false;
	}
}

bool SOC(char word[]){
	//初始检查函数->判断是否出现只有一个运算数的符号；合法返回true;非法返回false;
	int lenth=strlen(word);
	for(int i=0;i<lenth;i++){
		if(type(word[i])==1){//当前为数字
			if(i>0&&word[i-1]==')'){
				return false;
			}
			else{
				continue;
			}
		}
		else{//为符号
		    if(i==0){
		    	if(word[i]=='%'||word[i]=='*'||word[i]=='/'||word[i]=='^'){
		    		return false;
				}
				else{
					continue;
				}
			}
			else{
				if(word[i-1]=='('&&(word[i]=='%'||word[i]=='*'||word[i]=='/'||word[i]=='^')){
					return false;
				}
				else if(word[i]=='('&&(type(word[i-1])==1||word[i-1]==')')){
					return false;
				}
				else{
					continue;
				}
			}  	
		}
	}
	return true;
}

bool top2(int *num1,int *num2){
	//从数字栈内获得顶端两个数字的函数；成功返回true；不成功返回false
	if(num_stack.empty()!=true){
		*num2=num_stack.top();
		num_stack.pop();
		if(num_stack.empty()!=true){
			*num1=num_stack.top();
		    num_stack.pop();
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}


int main(){
	int time=0;
	scanf("%d\n",&time);
	for(int i=0;i<time;i++){
		//1.初始化
		memset(word,0,sizeof(word));
		while(num_stack.empty()!=true){
			num_stack.pop();
		}
		while(op_stack.empty()!=true){
			op_stack.pop();
		}
		tag=true;
		status=0;
		//2.读入内容并初步判断
		gets(word);
		if(SBC(word)==false){
			printf("error.\n");
			continue;
		}
		else if(SOC(word)==false){
			printf("error.\n");
			continue;
		}
		//初步判断合法，开始计算
		int lenth=strlen(word);
		int error=0;//记录可能出现的错误问题
		for(int i=0;i<lenth&&error==0;i++){
			if(type(word[i])==1){//当前位置为数字，开始拿数
				int place=i;
				while(type(word[place+1])==1){
				    //下一位也是数，就后移
					place++;
				}
				//执行结束后，数字的头在i,尾在place,正负由tag
				int num=gather(word,i,place,tag);
				i=place;//将i重定位
				num_stack.push(num);//数字进栈
				tag=true;//别忘了重置tag
				continue;
			}
			else{//当前位置为符号
				//先判断是不是正负号
				if(word[i]=='-'&&N(word,i)==true){
					//是负号,更新tag
					tag=false;
					continue;
				}
				else if(word[i]=='+'&&P(word,i)==true){
					//是正号，更新tag
					tag=true;
					continue;
				}
				else{//不是正负号
					if(op_stack.empty()==true){//空栈，直接进
						op_stack.push(word[i]);
						if(word[i]=='('){//是左括号
							status++;
						}
						continue;
					}
					else if(word[i]=='^'){//指数运算，直接进
						op_stack.push(word[i]);
						continue;
					}
					else if(word[i]=='('){//左括号，直接进
						op_stack.push(word[i]);
						status++;
						continue;
					}
					else if(word[i]==')'){//右括号，开弹
						while(op_stack.empty()!=true){//符号栈非空时
							char head=op_stack.top();
							if(head=='('){//为左括号
								op_stack.pop();
								break;//退出
							}
							else{//为其他符号，需要推出运算
								int num1,num2;
								if(top2(&num1,&num2)==false){//数字栈内数字不够,错误
									printf("error.\n");
									error++;
									op_stack.pop();
									break;
								}
								else{//栈内数字够
								    //此时需要运算，前数num1,后数num2,运算符head
									//先看合不合法
									if(legal(num1,num2,head)==false){
										//不合法
										if(head=='/'||head=='%'){////除数为零时
											printf("Divide 0.\n");
											error++;
										}
										else{//指数为负或其他算符
											printf("eror.\n");
											error++;
										}
										op_stack.pop();
										break;
									}
									else{
										//合法
										int result=cal(num1,num2,head);
										num_stack.push(result);//结果进栈
										op_stack.pop();//弹出符号
										continue;
									}
								}
							}
						}
						status--;
						continue;
					}
					else{//其他情况
						//看栈顶和待进栈符号
						char head=op_stack.top();
						if(compare(head,word[i],status)==false){//栈顶优先级低，进栈
							op_stack.push(word[i]);
							continue;
						}
						else{//栈顶高，开弹
							while(op_stack.empty()!=true){
								head=op_stack.top();
								if(compare(head,word[i],status)==false){
									break;//退出
								}
								else{
									//此时需要弹出head
									int num1,num2;
								    if(top2(&num1,&num2)==false){//数字栈内数字不够,错误
									    printf("error.\n");
									    error++;
									    op_stack.pop();
									    break;
								    }
								    else{//栈内数字够
								    //此时需要运算，前数num1,后数num2,运算符head
									//先看合不合法
									    if(legal(num1,num2,head)==false){
										//不合法
										    if(head=='/'||head=='%'){//除数为0
											    printf("Divide 0.\n");
											    error++;
										    }
										    else{//指数为负或其他算符
											    printf("error.\n");
											    error++;
										    }
										    op_stack.pop();
										    break;
									    }
									    else{
										//合法
										    int result=cal(num1,num2,head);
										    num_stack.push(result);//结果进栈
										    op_stack.pop();//弹出符号
										    continue;
										}
									}
								}
							}
							op_stack.push(word[i]);//新符号进栈
							continue;
						}
					}
				}
			}
		}
		//此时循环完成，验error
		if(error!=0){//有错误，已输出了，继续下一次
			continue;
		}
		else{//处理过程中无错误，进行终焉处理
		    //符号栈中无内容才行
		    while(op_stack.empty()!=true&&error==0){
		    	//开弹
		    	char head=op_stack.top();
		    	int num1=0,num2=0;
				if(top2(&num1,&num2)==false){//数字栈内数字不够,错误
					printf("error.\n");
					error++;
					op_stack.pop();
					break;
				}
				else{//栈内数字够
				//此时需要运算，前数num1,后数num2,运算符head
				//先看合不合法
				    if(legal(num1,num2,head)==false){
					//不合法
					    if(head=='/'||head=='%'){//除数为0
						    printf("Divide 0.\n");
						    error++;
					    }
					    else{//指数为负或其他算符
						    printf("error.\n");
						    error++;
					    }
					    op_stack.pop();
					    break;
				    }
				    else{
					//合法
					    int result=cal(num1,num2,head);
					    num_stack.push(result);//结果进栈
					    op_stack.pop();//弹出符号
					    continue;
				    }
				}
			}
			if(error!=0){
				continue;
			}
			else{
				//看数字栈内是否只剩一个数
				int final=num_stack.top();
				num_stack.pop();
				if(num_stack.empty()==true){
					printf("%d\n",final);
					continue;
				}
				else{
					printf("error.\n");
					continue;
				}
			}
		}
	}
}