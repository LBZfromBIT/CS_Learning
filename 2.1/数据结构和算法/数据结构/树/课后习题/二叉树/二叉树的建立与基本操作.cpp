#include <bits/stdc++.h>
using namespace std;

// 二叉树结点
struct TreeNode {
    char data;//数据元
    TreeNode* left;//左子树
    TreeNode* right;//右子树
};

// 建立二叉树
TreeNode* buildTree(char basic[],int& place,const int margin) {
	if(place==margin){//超界
		return NULL;
	}
    else if (basic[place]=='#') {//空树
        place++;
        return NULL;
    }
    else{//非空
    	TreeNode* root=(TreeNode*)malloc(sizeof(TreeNode));
        root->data=basic[place];
        place++;
        root->left = buildTree(basic,place,margin);
        root->right = buildTree(basic,place,margin);
        return root;
	}
}
void formatprint(TreeNode *root,int depth){
	if(root!=NULL){//非空时
		for(int i=0;i<depth;i++){
			printf("    ");
		}
		printf("%c\n",root->data);
		formatprint(root->left,depth+1);
		formatprint(root->right,depth+1);
	}
	return;
}

// 先序遍历
void preOrder(TreeNode* root) {
    if (root) {
        printf("%c",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
    return;
}

// 中序遍历
void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        printf("%c",root->data);
        inOrder(root->right);
    }
    return;
}

// 后序遍历
void postOrder(TreeNode* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%c",root->data);
    }
}

// 求叶子结点个数
int countLeaves(TreeNode* root) {
	if(root==NULL){
		return 0;
	}
    else if (root->left ==NULL&& root->right==NULL) {//为叶子结点
        return 1;
    }
    else{
    	return countLeaves(root->left) + countLeaves(root->right);
	}
}

// 交换左右子树
void swapChildren(TreeNode* root) {
    if (root!=NULL) {
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        swapChildren(root->left);
        swapChildren(root->right);
    }
    return;
}

int main() {
	char basic[100]={0};
	gets(basic);
	int lenth=strlen(basic);
	printf("BiTree\n");
	int place=0;
    TreeNode* root = buildTree(basic,place,lenth);//建树
    formatprint(root,0);//格式输出
    //先序
    printf("pre_sequence  : ");
    preOrder(root);
    printf("\n");
    //中序
    printf("in_sequence   : ");
    inOrder(root);
    printf("\n");
    //后序
    printf("post_sequence : ");
    postOrder(root);
    printf("\n");
    //叶子结点计数
    printf("Number of leaf: %d\n",countLeaves(root));
    printf("BiTree swapped\n");
    swapChildren(root);
    formatprint(root,0);//格式输出
    //先序
    printf("pre_sequence  : ");
    preOrder(root);
    printf("\n");
    //中序
    printf("in_sequence   : ");
    inOrder(root);
    printf("\n");
    //后序
    printf("post_sequence : ");
    postOrder(root);
    printf("\n");
    return 0;
}