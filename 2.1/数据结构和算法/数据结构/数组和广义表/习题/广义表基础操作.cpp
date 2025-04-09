#include <bits/stdc++.h>

/*基本思路：
    按书上操作来，使用头尾指针法建立广义表
*/

//全局变量域
typedef struct node{
	bool visit;//是否访问过的标签（是->true;否->false)
	int tag;//该节点储存类型的标签（0->原子结点；1->表）
	struct node *tlink;//表尾内容指针（指向后继节点）
	union{//表头内容共用体
		char data;//原子结点的数据
		struct node *hlink;//子表内容指针
	}val;
}GList;

void Create(char s[],int& i,GList*& g){//建立表的函数
    /*
    由于表的定义是递归的
	即：表=表头（原子or子表）+表尾（一定是个表）
	因此可以递归的实现写入表的操作
    */
    
	if(s[i]!='\0'){//字符串未结束(此处无需循环->因为i是引用参数，会在后续递归的过程中一点点变大）
		char ch=s[i];//取出当前字符
		i++;//i下移一位
		if(ch=='('){//左括号，表的开始
			if(s[i]==')'){//表为空表
				g=NULL;//其结点指针置空
				i++;//跳过右括号继续
			}
			else{//表非空，处理表头结点
				g=(GList*)malloc(sizeof(GList));//建立表结点
				g->visit=false;
				g->tag=1;
				Create(s,i,g->val.hlink);//递归建立表头结点
				Create(s,i,g->tlink);//递归建立表尾结点
			}
		}
		else if(ch==')'){//右括号，表结束
			g=NULL;
		}
		else if(ch==','){//逗号，之后内容为表尾
			g=(GList*)malloc(sizeof(GList));
			g->visit=false;
			g->tag=1;
			Create(s,i,g->val.hlink);//递归的建立表尾的表头
			Create(s,i,g->tlink);//递归的建立表尾的表尾
		}
		else{//单个字母的情况，为原子结点
			g=(GList*)malloc(sizeof(GList));
			g->visit=false;
			g->tag=0;
			g->tlink=NULL;
			g->val.data=ch;
		}
	}
	return;
}