#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef int keyType ; // 节点key的类型
typedef struct BitNode {
    keyType key;   // 节点的key 也就是 存放的data
    BitNode* lNode; // 左孩子
    BitNode* rNode; // 右孩子
}*BitTree;
// 非递归查找
BitNode *BST_Search_NoRecursion(BitTree T,keyType key);
BitNode *BST_Search(BitTree T,keyType key);
int BST_Insert(BitTree &T,keyType key);
void BST_Create(BitTree &T,keyType keys[],int n);
BitNode *BST_Delete(BitTree &T,int key);

BitNode *minValueNode(BitNode *pNode);

int main() {

    return 0;
}

// 非递归查找
BitNode *BST_Search_NoRecursion(BitTree T,keyType key){
    while (T!=NULL && key != T->key){
        if (key < T->key) T = T->lNode;
        else T = T->rNode;
    }
    return T;
}
// 递归查找
BitNode *BST_Search(BitTree T,keyType key){
    if (T == NULL || key == T->key) return T;
    else if (key < T->key)
       return BST_Search(T->lNode,key);
    else
       return BST_Search(T->rNode,key);
}
/**
 *  二叉排序树的插入操作
 * @param T  二叉排序树
 * @param key  要插入的值
 * @return  是否插入成功  1 为成功 0 为  fail
 */
int BST_Insert(BitTree &T, keyType key) {
    if (T == NULL) {
        T = (BitTree) malloc(sizeof(BitNode)); // 声明空间
        T->key = key;
        T->lNode = T->rNode = NULL;
        return 1;
    } else if (T->key == key) {
        return 0;           // 插入失败 已经有相同结点了
    } else if (key < T->key) {
        return BST_Insert(T->lNode,key);    // 插入右子树
    }else{
        return BST_Insert(T->rNode,key);    // 插入左子树
    }
}

/**
 * 二叉排序树的创建
 * @param T : 二叉排序树
 * @param keys ：要插入的数组
 * @param n     ：数组长度
 */
void BST_Create(BitTree &T,keyType keys[],int n){
    T = NULL;
    for (int i = 0; i < n; ++i) {
        BST_Insert(T,keys[i]);
    }
}

BitNode *BST_Delete(BitTree &T,int key){
    if (T == NULL){ // 如果为空 直接返回
        return T;
    }
    if (key > T->key){   // 如果 大于 就去右子树寻找
        T->rNode =  BST_Delete(T->rNode,key); // T 的 右子树 就等于删除该节点后的右子树
    }
    else if(key < T->key){      // 如果 小于 就去左子树寻找
        T->lNode =  BST_Delete(T->lNode,key);  // T 的 左子树
    }
    else{   // == 也就是已经找到要删除的节点。
        if (T->lNode == NULL ){   // 如果有左子树为空
            BitNode *temp = T->rNode;   // 右子树保存起来
                free(T);        // 删除这个顶点
            return temp;    // 回去 “接上右子树”
        }else if(T->rNode == NULL){  // 如果只有至多一个结点
            BitNode *temp = T->lNode;
            free(T);
            return temp;
        }

        // 最难的情况 如果 左右都不为空
        BitNode *temp = minValueNode(T->rNode); // 找到 右子树的最小值顶点

        // 偷梁换柱
        T->key = temp->key; // 顶点被替换了
        T->rNode = BST_Delete(T->rNode,temp->key);  // 掩盖事实 删除原来最小值顶点
    }

}

// 找到右子树的最小值
BitNode *minValueNode(BitNode *pNode) {
    return nullptr;
}
