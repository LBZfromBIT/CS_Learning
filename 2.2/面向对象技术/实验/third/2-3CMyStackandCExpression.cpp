#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class CMyStack{
private:
	double *m_pTop;//top pointer of stack
	int m_iSize;//NUmber of actual elemnets
	int m_iCapacity;//Cpacity of stack
public:
	CMyStack(int size);//Set the capacity of stack
	~CMyStack();
	double Pop();
	double Peek();
	bool Push(double ch);
	bool isEmpty();//is stcak empty?
	bool isFull();//is Stack full?
	int GetSize();//get number of actual elements
	void Clear();//Clear stack
};
//the constructor function
CMyStack::CMyStack(int size=100){
	m_pTop=new double[size];
	m_iCapacity=size;
	m_iSize=0;
}
//the distructor function
CMyStack::~CMyStack(){
	if(m_pTop!=nullptr){
		delete[] m_pTop;
	}
}
//the pop function
double CMyStack::Pop(){
	assert(m_iSize>0);
	m_iSize--;
	double temp=m_pTop[m_iSize];
	m_pTop[m_iSize]=0;
	return temp;
}
//the peek function
double CMyStack::Peek(){
	assert(m_iSize>0);
	return m_pTop[m_iSize-1];
}
//the push funtion
bool CMyStack::Push(double ch){
	if(m_iSize>m_iCapacity){
		cout<<"Full."<<endl;
		return false;
	}
	m_pTop[m_iSize]=ch;
	m_iSize++;
	return true;
}
//the empty function
bool CMyStack::isEmpty(){
	if(m_iSize==0){
		return true;
	}
	else{
		return false;
	}
}
//the full function
bool CMyStack::isFull(){
	if(m_iSize>m_iCapacity){
		return true;
	}
	else{
		return false;
	}
}
//the getsize function
int CMyStack::GetSize(){
	return m_iSize;
}
//the clear function
void CMyStack::Clear(){
	for(int i=0;i<m_iSize;i++){
		m_pTop[i]=0;
	}
	m_iSize=0;
	return;
}

class CExpression{
private:
	CMyStack num;//the number stack
	CMyStack op;//the operator stack
	string exp;//to store the expression
public:
	CExpression(string s);
	void SetExpression(string s);
	double opera(double a,double b,char opt);
	double Value();
	bool OpBet(char ahead,char after,int flag);
	friend ostream& operator << (ostream& os,const CExpression& expr);
};
//the constructor function
CExpression::CExpression(string s){
	exp=s;
}
//the reset function
void CExpression::SetExpression(string s){
	exp=s;
	num.Clear();
	op.Clear();
}
//the operator function
double CExpression::opera(double a,double b,char opt){
	switch (opt){
	case '+':
		return a+b;
	case '-':
		return a-b;
	case '*':
		return a*b;
	case '/':
		return a/b;
	default:
		cout<<"wrong."<<endl;
		return 0;
	}
	
}
//the value function
double CExpression::Value(){
	int lenth=exp.length();
	int ptr=0;//the interator
	int flag=0;//to show if the interator is in brackets
	while(ptr<lenth){
		if(exp[ptr]>='0'&&exp[ptr]<='9'){//as for number
			//get sum
			double sum=0;//the sum
			bool tag=false;//the tag to show if the number is float
			double level=1;//the level of float
			while(ptr<lenth&&((exp[ptr]>='0'&&exp[ptr]<='9')||exp[ptr]=='.')){
				if(exp[ptr]=='.'){
					tag=true;
					ptr++;
					continue;
				}
				if(tag==false){
					sum=sum*10+(exp[ptr]-'0');
					ptr++;
					continue;
				}
				else{
					level=level*0.1;
					sum+=(exp[ptr]-'0')*level;
					ptr++;
					continue;
				}
			}
			//till this place,the ptr will stop behind the last digit of number
			num.Push(sum);
		}
		else{//as for operator
			if(exp[ptr]=='('){//the highest priority
				flag++;
				op.Push((double)exp[ptr]);
				ptr++;
			}
			else if(exp[ptr]==')'){//the lowest priority
				flag--;
				while(op.isEmpty()!=true&&op.Peek()!='('){//pop out all the operatoer till the nearest left bracket
					double after=num.Pop();
					double ahead=num.Pop();
					char opt=(char)op.Pop();
					double result=opera(ahead,after,opt);
					num.Push(result);
				}
				op.Pop();//pop out the left bracket
				ptr++;
				continue;
			}
			else{//for the other operators
				if(op.isEmpty()==true){
					op.Push((double)exp[ptr]);
					ptr++;
					continue;
				}
				else{
					char ahead=(char)op.Peek();
					char after=(char)exp[ptr];
					if(OpBet(ahead,after,flag)==false){//the after has high priority
						op.Push((double)exp[ptr]);
						ptr++;
						continue;
					}
					else{//the ahead has high priority
						while(OpBet(ahead,after,flag)==true){
							double afternum=num.Pop();
							double aheadnum=num.Pop();
							char opt=(char)op.Pop();
							double result=opera(aheadnum,afternum,opt);
							num.Push(result);
							if(op.isEmpty()==true){
								break;
							}
							else{
								ahead=(char)op.Peek();
								continue;
							}
						}
						op.Push((double)exp[ptr]);
						ptr++;
						continue;
					}
				}
			}
		}
	}
	//till this place the expression has been finished
	while(op.isEmpty()==false){
		char opt=(char)op.Pop();
		double afternum=num.Pop();
		double aheadnum=num.Pop();
		double result=opera(aheadnum,afternum,opt);
		num.Push(result);
		continue;
	}
	return num.Peek();
}
//the functiontos show which operator has priority
bool CExpression::OpBet(char ahead,char after,int flag){
	if(flag==0){
		//not in bracket
		if(ahead=='('){
			switch (after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return true;
			case '/':
				return true;
			}	
		}
		else if(ahead=='+'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return false;
			case '/':
				return false;
			}
		}
		else if(ahead=='-'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return false;
			case '/':
				return false;
			}
		}
		else if(ahead=='*'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return true;
			case '/':
				return true;
			}
		}
		else if(ahead=='/'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return true;
			case '/':
				return true;
			}
		}
	}
	else if(flag>0){
		//in bracket
		if(ahead=='('){
			switch(after){
			case '+':
				return false;
			case '-':
				return false;
			case '*':
				return false;
			case '/':
				return false;
			}
		}
		else if(ahead=='+'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return false;
			case '/':
				return false;
			}
		}
		else if(ahead=='-'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return false;
			case '/':
				return false;
			}
		}
		else if(ahead=='*'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return true;
			case '/':
				return true;
			}
		}
		else if(ahead=='/'){
			switch(after){
			case '+':
				return true;
			case '-':
				return true;
			case '*':
				return true;
			case '/':
				return true;
			}
		}
	}
	
	cout<<"wrong."<<endl;
	return false;
}
//the cout function
ostream& operator << (ostream& os,const CExpression& expr){
	cout<<expr.exp;
	return os;
}

int main(){
	CExpression expr("50.3-20.12+8*8/2");
	cout<<expr<<"="<<expr.Value()<<endl;
	
	expr.SetExpression("55.99-88.11+77.12");
	cout<<expr<<"="<<expr.Value()<<endl;
	
	expr.SetExpression("(39+11)*30+10/5");
	cout<<expr<<"="<<expr.Value()<<endl;
	
	expr.SetExpression("39+12*(47+33)");
	cout<<expr<<"="<<expr.Value()<<endl;
	
	expr.SetExpression("20/(112-(10*1.2))/10-1.01");
	cout<<expr<<"="<<expr.Value()<<endl;
	
	expr.SetExpression("20/(112-10*1.2)/10-1.01");
	cout<<expr<<"="<<expr.Value()<<endl;
	
	cout<<"ENDING…"<<endl;
	return 0;
}