//
// Created by Dell on 2022-11-02.
//  堆排序
//

#include "heapsort.h"
#include "iostream"

using namespace std;

/**
 *最大堆的构建
 * 根据最大堆的性质，我们可以知道 以下几点
 * 1）一定是一个完全树  -- 也就是说 叶子结点只能出现在最下层和次下层，且最下层的叶子结点集中在树的左部。
 * 2）根结点一定比左右子树的大
 * 3）从底部进行交换，比如下标值为i的左孩子下标为 2*i+1  右孩子下标为 2*i+2
 * @param a 数组
 * @param start 起始下标（从哪里开始构建最大堆）
 * @param end  截止下标 （到哪里结束）
 */
void maxHeapDown(int *a, int start, int end){
    int c = start;      // 当前结点
    int l = 2*c + 1;        // 结点的左孩子
    int tmp = a[c];         // 结点的值
    for (;l<=end; c=l,l=2*l+1) {
        // 找到左右孩子的最大值
        if (a[l] < a[l+1])  // 如果左子树的值 < 右孩子的值
            l++;     //l 指向右孩子
        // 如果根结点 > 左右孩子 就可以退出构建了
        // 因为 这是一个最大堆，左右孩子均为一个最大堆。所以 如果根结点已经是最大了 就表明它是这些节点中最大的了
        if (tmp >= a[l])
            break;
        else{   // 不是 就要跟l交换，而且交换完，a[l]这个结点的值也就不一定比左右孩子都大了，就要继续调整下去
            a[c] = a[l];
            a[l] = tmp;
        }
    }
}

/**
 * 构建最大堆
 * @param a 数组
 * @param n 数组长度
 */
void buildMaxHeap(int *a,int n){
    // 最后一个下标为 n-1 if最后一个结点是右子树，那么他的父节点满足 2*i+2 = n-1 => i = n/2 - 1
                    //if 最后一个结点是左子树 那么 2*i +1 = n-1 => i = n/2 -1

    // 从最后一个结点的父节点开始
    for (int i = n/2 - 1; i >=0 ; --i) {
        maxHeapDown(a,i,n-1);
    }
}

/**
 * 堆排序 升序
 * @param a
 * @param n
 */
void heap_sortASC(int *a,int n){
    buildMaxHeap(a,n);  // 构建最大堆
    for (int i = n-1; i > 0; --i) { // n-1次交换
        swap(a[0],a[i]);    // 将最后一个跟第一个进行交换
        buildMaxHeap(a,i-1);
    }
}

/**
 * 最小堆的构建 ，跟要比左右孩子都小
 * @param a 数组
 * @param start 起始位置
 * @param end 最终位置
 */
void minHeapDown(int *a,int start,int end){
    int c = start;
    int l = c*2+1;
    int tmp = a[c];
    for (; l <=end ;c=l,l=2*l+1) {
        if (l<end && a[l] > a[l+1])
            l++;
        if (tmp <= a[l])
            break;
        else{
            a[c] = a[l];
            a[l] = tmp;
        }
    }
}

/**
 * 构建最小堆
 * @param a 数组
 * @param n 数组长度
 */
void buildMinHeap(int *a,int n){
    for (int i = n/2-1; i >=0 ; i--) {
        minHeapDown(a,i,n-1);
    }
}

void heap_sortDES(int *a,int n){
    buildMinHeap(a,n);
    for (int i = n-1; i >0 ; --i) {
        swap(a[0],a[i]);
        buildMinHeap(a,i);
    }
}



