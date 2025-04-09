#include <bits/stdc++.h>
#define max_size 100

/*
基本思路：
    先读入字符串，并从第一个开始向后遍历
    如果为字符-->可以直接输出
    如果为运算符-->是左/括号-->左括号直接进栈，tag++;
	                           右括号不进栈，并且将一直弹出栈顶，直到遇到左括号
                     
	               非括号-->需要结合括号内外来判断优先级
                   a.如果在括号内（tag>0)
                    优先级:^大于*、/大于+、-大于（大于）
                   b.如果在括号外（tag!>0)
                    优先级：（大于^大于*大于/大于+大于-大于）
        保证符号栈为算符优先级单调增栈-->每次符号进栈时，先弹出栈顶比他运算优先级高的算符
*/

//函数区
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
		else if(op1=='*'||op1=='/'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
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
		else if(op1=='*'||op1=='/'){
			if(op2=='^'){
				return false;
			}
			else if(op2=='*'){
				return true;
			}
			else if(op2=='/'){
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

void trans(char word[],int size){
	//实现转换输出的函数，word为待转换数组，size为字符串长
	int status=0;//括号tag
	std::stack <char> op_stack;//符号栈
	for(int i=0;i<size;i++){
		if((word[i]>='A'&&word[i]<='Z')||(word[i]>='a'&&word[i]<='z')){//运算数，输出
			printf("%c",word[i]);
			continue;
		}
		else{//运算符
			if(op_stack.empty()==true){//空栈，直接放
				op_stack.push(word[i]);
				if(word[i]=='('){//为左括号
					status++;//tag++
				}
				continue;
			}
			else{//栈非空
				if(word[i]=='('){//左括号直接进栈
					op_stack.push(word[i]);
					status++;
					continue;
				}
				/*由于指数运算的右结合性，两个^运算符实际上后面的优先级高
				else if(word[i]=='^'){//指数运算->右结合->指数算符直接进栈
					op_stack.push(word[i]);
					continue;
				}
				*/
				else if(word[i]==')'){//右括号，弹
				    status--;
					while(op_stack.empty()!=true){//栈非空状态下
						char head=op_stack.top();
						if(head!='('){//输出非左括号
							printf("%c",head);
							op_stack.pop();
							continue;
						}
						else{//栈顶为左括号
							op_stack.pop();
							break;
						}
					}
				}
				else{//其余符号
				    //判断优先级
					char head=op_stack.top();
					if(compare(head,word[i],status)==true){//栈顶优先级高，弹出高
						while(op_stack.empty()!=true){//非空情况下
							head=op_stack.top();
							if(compare(head,word[i],status)==true){
								printf("%c",head);
								op_stack.pop();
								continue;
							}
							else{
								break;
							}
						}
						op_stack.push(word[i]);
					}
					else{//栈顶优先级低,word[i]进栈
						op_stack.push(word[i]);
						continue;
					}
				}
			}
		}
	}
	//遍历完后，输出栈内剩余内容
	while(op_stack.empty()!=true){
		char head=op_stack.top();
		printf("%c",head);
		op_stack.pop();
		continue;
	}
	printf("\n");
}

//全局变量区
char word[max_size];

int main(){
	int time=0;
	scanf("%d\n",&time);
	for(int i=1;i<=time;i++){
		memset(word,0,sizeof(word));//先重置
		gets(word);
		trans(word,strlen(word)-1);//此处减一为了抛掉#
	}
	return 0;
}