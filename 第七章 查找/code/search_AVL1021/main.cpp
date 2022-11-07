#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct AVLNode *Tree;
typedef int ElementType;
typedef struct AVLNode{
    ElementType element;    // 存放数据
    Tree lChild;    // 左子树
    Tree rChild;    // 右子树
    int height;     //节点深度
}AVLNode;

Tree LL_rotate(Tree pNode); // 右旋
Tree RR_rotate(Tree pNode); // 左旋
Tree LR_rotate(Tree pNode); // 先左旋后右旋
Tree RL_rotate(Tree pNode); // 先右旋后左旋
int height(Tree p);
Tree insert(Tree T,int X);
int Max(int l_number, int r_number);
void printTree(Tree T);
int main() {
    int arr[] = { 3,  2,  1,  4,  5,  6,  7,  16,  15,  14,  13,  12,  11,  10,  8,  9};
    Tree T = NULL;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        T = insert(T,arr[i]);
    }
    printTree(T);
    return 0;
}

void printTree(Tree T){
    if (T == NULL)
        return;
    else{
        printTree(T->lChild);
        cout<<T->element<<" ";
        printTree(T->rChild);
    }
}
/**
 * 右旋
 * A的左孩子的左子树插入结点 导致不平衡   需要一次右旋,步骤如下
 * 1) 新平衡二叉树的根结点 = 失衡结点的 左子树
 * 2） 失衡二叉树的左子树 = 新根结点的右子树
 * 3） 新根结点的右子树  = 失衡结点
 * @param pNode  失衡结点
 * @return  新的平衡二叉树
 */
Tree LL_rotate(Tree pNode) {
    Tree newParent =pNode->lChild;   // 新二查平衡树的根结点为 中断结点 的 左子树
    pNode->lChild = newParent->rChild;  // 中断结点的 左子树 =  现在根结点的 右子树
    newParent->rChild = pNode;      // 现在根结点 的 右子树 = 中断节点
    // 更新结点高度
    newParent->height = Max(height(newParent->lChild),height(newParent->rChild)) + 1;
    pNode->height = Max(height(pNode->lChild),height(pNode->rChild)) + 1;
    return newParent;
}

/**
 *  向A的右孩子的右子树插入结点 ---- 需要一次左旋，步骤如下
 *  1）  新树的根结点  = 失衡结点的右子树
 *  2)  失衡结点的 右子树  = 新树的左子树
 *  3） 新树的左子树 = 失衡结点
 * @param pNode 出现不平衡的结点
 * @return  新的一颗平衡二叉树
 */
Tree RR_rotate(Tree pNode){
    Tree newParent = pNode->rChild; // 步骤一
    pNode->rChild = newParent->lChild;
    newParent->lChild = pNode;
    // 更新结点的高度
    newParent->height = Max(height(newParent->lChild),height(newParent->rChild)) + 1;
    pNode->height = Max(height(pNode->lChild),height(pNode->rChild)) + 1;
    return newParent;
}

/**
 * 向 A的 左孩子的右孩子插入了结点  -- 需要两次旋转 -- 对A的左孩子左旋 对A 右旋
 * @param pNode 失衡点
 * @return 新的平衡二叉树
 */
Tree LR_rotate(Tree pNode){
    pNode->lChild = RR_rotate(pNode->lChild);
    return LL_rotate(pNode);
}

/**
 * 向A结点的右孩子的左孩子插入结点
 * 先将右孩子右旋 在将整体左旋
 * @param pNode 失衡点
 * @return  新的平衡二叉树
 */
Tree RL_rotate(Tree pNode){
   pNode->rChild = LL_rotate(pNode->rChild);    // 右孩子右旋
    return RR_rotate(pNode);        // 整体左旋
}

/**
 *  向新的平衡二叉树添加新的值
 * @param T 平衡二叉树
 * @param X 要插入的值
 * @return 新的平衡二叉树
 */
Tree insert(Tree T,int X){
    if (T == NULL){ // 查无此树
        T = (Tree) malloc(sizeof (AVLNode));
        T->element = X;
        T->height = 0;
        T->lChild= T->rChild = NULL;
    }else if (X < T->element){   // X的值小于 X 往左子树找
        T->lChild = insert(T->lChild,X);    // 跟二叉排序树一样 递归插入
        if (height(T->lChild) - height(T->rChild) == 2){    // 向左子树插入 ，左子树高度大
            // 如果 高度差为2 就说明破坏了平衡 需要重新平衡
            if (X<T->lChild->element){ // 根据 小的放左边 大的放右边 判断是哪种类型
                // LL 型
               T =  LL_rotate(T);
            }else{
                // LR型
                T = LR_rotate(T);
            }
        }
    } else if (X > T->element){ // 向右子树插入
        T->rChild = insert(T->rChild,X);
        if (height(T->rChild) - height(T->lChild) == 2){    // 向右插入 破坏了平衡
            if (X> T->rChild->element){
                // RR 型 向 右孩子的右子树插入
                T = RR_rotate(T);
            }else{
                T = RL_rotate(T);
            }
        }
    }
    T->height = Max(height(T->lChild), height(T->rChild)) +  1;
    return T;
}

/**
 *
 * @param l_number 第一个数
 * @param r_number 第二个数
 * @return 最大的数
 */
int Max(int l_number, int r_number) {
    return l_number > r_number?l_number:r_number;
}

/**
 *
 * @param p  根结点
 * @return 树的高度
 */
int height(Tree p) {
    if ( p == NULL)
        return -1;
    else
        return p->height;
}
