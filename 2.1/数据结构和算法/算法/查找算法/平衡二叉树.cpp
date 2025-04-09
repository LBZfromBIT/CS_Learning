#include <bits/stdc++.h>
using namespace std;

//全局变量域
struct node{
	char val;//值
	node* left;//左子树
	node* right;//右子树
	int high;//该节点高度
};

//全局函数域
node* cn(char ch){//建立新节点函数
	node* nn=new(node);
	nn->val=ch;
	nn->left=NULL;
	nn->right=NULL;
	nn->high=0;
	return nn;
}

int gethigh(node*& root){//获得某个节点高度的函数，叶子节点高度为0
	if(root!=NULL){//ver2.0实现在递归过程中更新高度
		root->high=1+max(gethigh(root->left),gethigh(root->right));//左右子节点高度大值+1
		return root->high;
	}
	else{
		return -1;
	}
}

int getbal(node*& root){//获得某个节点的平衡因子，-1为左少1,0为平衡，1为右少1
	if(root!=NULL){
		return gethigh(root->left)-gethigh(root->right);
	}
	else{
		return 0;
	}
}

node* LT(node*& root){//左转函数
	node* newroot=root->right;//新的根节点
	if(newroot->left!=NULL){//新根节点的左子树交给老根节点的右子树
		root->right=newroot->left;
	}
	else{
		root->right=NULL;
	}
	newroot->left=root;
	return newroot;
}

node* RT(node*& root){//右转函数
	node* newroot=root->left;
	if(newroot->right!=NULL){
		root->left=newroot->right;
	}
	else{
		root->left=NULL;
	}
	newroot->right=root;
	return newroot;
}

node* update(node*& root,char ch){//动态更新树的函数
	if(root==NULL){//空点则插
		root=cn(ch);
		return root;
	}
	else if(root->val==ch){//已经存在，不管
		return root;
	}
	else if(root->val<ch){//ch大，落入右子树
		root->right=update(root->right,ch);
	}
	else{//ch小，落入左子树
		root->left=update(root->left,ch);
	}
	
	//开始调整平衡
	root->high=gethigh(root);//更新树高
	int bal=getbal(root);
	if(bal<-1){//左边矮，右子树高
		if((root->right!=NULL)&&(getbal(root->right)<=0)){
			//RR型，一次左转
			return LT(root);
		}
		else{
			//RL型，
			root->right=RT(root->right);
			return LT(root);
		}
	}
	else if(bal>1){//左边高，右边低
		if((root->left!=NULL)&&(getbal(root->left)>=0)){
			//LL型，一次右转
			return RT(root);
		}
		else{
			root->left=LT(root->left);
			return RT(root);
		}
	}
	else{//等高
		return root;
	}
}

void fp(node* root){//先序遍历
	if(root==NULL){
		return;
	}
	else{
		printf("%c",root->val);
		fp(root->left);
		fp(root->right);
		return;
	}
}

void mp(node* root){//中序遍历
	if(root==NULL){
		return;
	}
	else{
		mp(root->left);
		printf("%c",root->val);
		mp(root->right);
	}
}

void bp(node* root){//后序遍历
	if(root==NULL){
		return;
	}
	else{
		bp(root->left);
		bp(root->right);
		printf("%c",root->val);
	}
}

void tp(node* root,int space){//树形输出
	if(root==NULL){
		return;
	}
	else{
		tp(root->right,space+4);
		for(int i=0;i<space;i++){
			printf(" ");
		}
		printf("%c\n",root->val);
		tp(root->left,space+4);
	}
}

int main(){
	char str[1000]={0};
	gets(str);
	int lenth=strlen(str);
	
	node* root=NULL;
	for(int i=0;i<lenth;i++){
		root=update(root,str[i]);
	}
	
	printf("Preorder: ");
	fp(root);
	printf("\n");
	
	printf("Inorder: ");
	mp(root);
	printf("\n");
	
	printf("Postorder: ");
	bp(root);
	printf("\n");
	
	printf("Tree:\n");
	tp(root,0);
	
	return 0;
}