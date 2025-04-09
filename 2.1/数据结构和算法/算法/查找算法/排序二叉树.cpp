#include <bits/stdc++.h>
using namespace std;

//全局变量域
struct node{
	int val;//数值
	node* left;//左子树指针
	node* right;//右子树指针
};

//全局函数域
node* cn(int number){//创造新节点函数
	node* nn=new(node);
	nn->val=number;
    nn->left=NULL;
	nn->right=NULL;
	return nn;
}

void update(node*& root,int number){//更新排序二叉树函数
	if(root==NULL){
		root=cn(number);
		return;
	}
	else if(root->val<=number){//a的值比当前根节点大,放在右子树
		update(root->right,number);
		return;
	}
	else if(root->val>number){//a的值比当前根节点小，放在左子树
		update(root->left,number);
		return;
	}
}

void midprint(node* root){//中序遍历
	if(root!=NULL){
		midprint(root->left);
		printf(" %d",root->val);
		midprint(root->right);
		return;
	}
	else{
		return;
	}
}

void printtree(node* root,int space){//凸入遍历
	//其中space表示缩进空间
	if(root!=NULL){
		if(root->left!=NULL){
			printtree(root->left,space+4);
		}
		for(int i=0;i<space;i++){
			printf(" ");
		}
		printf("%d\n",root->val);
		if(root->right!=NULL){
			printtree(root->right,space+4);
		}
		return;
	}
	else{
		return;
	}
}

int main(){
	node* root=NULL;
	int num;
	scanf("%d",&num);
	while(num!=0){
		update(root,num);
		scanf("%d",&num);
	}
	printtree(root,0);
	printf("\n");
	midprint(root);
	printf("\n");
}