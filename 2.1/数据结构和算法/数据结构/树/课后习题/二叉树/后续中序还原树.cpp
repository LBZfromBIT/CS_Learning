#include <bits/stdc++.h>
using namespace std;
 
struct Node
{
    char data;//数据元
    Node* left;//左子树
    Node* right;//右子树
};
 
// 创建新节点
Node* NewNode(char data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
 
// 找到在中序遍历序列中的索引位置
int Search(string mid, int start, int end, char value)
{
    int i;
    for (i = start; i <= end; i++)
    {
        if (mid[i] == value) {
            return i;
        }
    }
    return i;
}
 
// 使用中序和后序遍历序列构建二叉树
Node* BuildTree(string mid, string back, int midStart, int midEnd)
{
    static int backIndex = midEnd;
    if (midStart > midEnd) {
        return NULL;
    }
    // 创建新的节点，backIndex位置是根节点
    Node* node = NewNode(back[backIndex--]);
    if (midStart == midEnd) {
        return node;
    }
    // 在中序数组中找到此节点的索引
    int midIndex = Search(mid, midStart, midEnd, node->data);
    // 递归构建左右子树
    node->right = BuildTree(mid, back, midIndex + 1, midEnd);
    node->left = BuildTree(mid, back, midStart, midIndex - 1);
    return node;
}
 
// 打印层次遍历序列
void PrintLevel(Node* root)
{
    if (root == NULL)  return;
    queue<Node*> q;
    q.push(root);
    while (q.empty()!=true)
    {
        int nodeCount = q.size();
        while (nodeCount > 0)
        {
            Node* node = q.front();
            cout << node->data;
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
    }
    cout << endl;
}
 
// 主函数
int main()
{
    string mid;
    string back;
    cin >> mid >> back;
    int lenth = mid.size();
    Node* root = BuildTree(mid, back, 0, lenth-1);
    PrintLevel(root);
    return 0;
}