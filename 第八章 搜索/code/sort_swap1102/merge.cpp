//
// Created by Dell on 2022-11-03.
//

#include "merge.h"
#include "iostream"
#include "stdlib.h"
using namespace std;

void mergeGroup(int *a, int gap, int n);

using namespace std;

/**
 * 将两个有序区间 合并成 一个
 * @param a 数组
 * @param start 区间一的起始下标
 * @param mid   区间一的终点 区间而的起点
 * @param end   区间二的终点
 */
void merge(int *a,int start,int mid,int end){
    int *tmp =new int[end-start+1]; // tmp将两个区间进行合并
    int i = start;  // 区间一的起始下标
    int j = mid +1; // 区间二的起始下标
    int k = 0 ;     // 记录tmp数组的下标
    while (i<=mid && j<=end){
        if (a[i]<a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    // 将还没有放入数组中的放入
    while (i <= mid)
        tmp[k++] = a[i++];
    while (j<=end)
        tmp[k++] = a[j++];

    // 将排序好的tmp 赋值给 a
    for (int l = 0; l < k; ++l) {
        a[start+l] = tmp[l];
    }

    delete[] tmp;   // 释放tmp
}

/**
 * 归并排序 从上到下    -- 递归
 * @param a 数组
 * @param start 开始下标
 * @param end   结束下标
 */
void mergeSortUp2Down(int *a,int start,int end){
    if (a==NULL || start >= end)
        return;
    int mid = (start + end) / 2;
    mergeSortUp2Down(a,start,mid);  // 递归进行合并排序 得到的就是一个 [start ... mid] 的 有序数列
    mergeSortUp2Down(a,mid+1,end);  // 同理  得到的是 [mid+1 ... end] 有序数列
    merge(a,start,mid,end); // 合并
}

/**
 * 归并排序 从下到上    -- 非递归
 * @param a 数组长度
 * @param n 数组长度
 */
void mergeSortDown2Up(int *a,int n){
    if (a == NULL || n <= 0)
        return;
    for (int i = 1; i < n; i*=2) {
        mergeGroup(a,i,n);
    }
}

/**
 *  自低至上   分组合并
 * @param a 数组
 * @param gap 区间长度
 * @param n 数组长度
 */
void mergeGroup(int *a, int gap, int n) {
    int i ;
    for (i = 0; i + 2*gap <n  ; i += 2*gap) {
        merge(a,i,i+gap-1,i+2*gap-1);
    }

    //如果有一个区间没有合并 ，就让他跟前一个进行合并
    if (i+gap<n){
        merge(a,i,i+gap-1,n-1);
    }
}

/**
 *  计数排序算法
 * @param a 数组
 * @param n 数组长度
 */
void countSort(int *a,int n){
    int *count_arr = (int *) malloc(sizeof(int) * n);   // 计数数组
    int *result_arr = (int *)malloc(sizeof(int) * n);   // 排序结果数组

    // 计数数组 初始化
    for (int i = 0; i < n; ++i) {
        count_arr[i] = 0;
    }
    for (int j = 0; j < n; ++j) {
        count_arr[a[j]]++;      // 计数
    }


    // 找到每个元素的下标范围
    for (int k = 1; k < n; ++k) {
        count_arr[k] = count_arr[k] + count_arr[k-1];
    }
    for (int i = n-1; i >= 0 ; i--) {
        result_arr[count_arr[a[i]] - 1] = a[i];
        count_arr[a[i]] --;
    }
    for (int i = 0; i < n; ++i) {
        a[i] = result_arr[i];
    }
}



// 基数排序
/**
 * 求出 数组中的 最大位数
 * @param a 数组
 * @param n 数组长度
 * @return  最大位数
 */
int getMax(int a[],int n){
   // 先求出最大值
   int max = a[0];
   for (int i = 1; i < n; ++i) {
       if (a[i] > max)
           max = a[i];
    }

   int d = 1;
    while (max >= 10){
        max /= 10;
        d++;
    }

    return d;
}

/**
 *  基数排序
 * @param a 数组
 * @param n 数组长度
 */
void radixSort(int *a,int n){
   int d = getMax(a,n);
   int *tmp = (int *) malloc(sizeof(int) * n);
   int *count = (int *) malloc(sizeof(int) * n);
   int radix = 1;       // 第几位数
    for (int i = 1; i <=d ; ++i) {  // 执行d次， 从个位 到 d位
        // 每次 都要把桶 初始化
        for (int j = 0; j < 10; ++j) {
            count[j] = 0;
        }
        // 提出每个数的第d位，然后使用计数算法
        for (int k = 0; k < n; ++k) {
            int num = (a[k] / radix) % 10;  // 提出个位、十位...
            count[num]++;
        }
        // 计数排序的常规操作
        for (int j = 1; j < 10; ++j) {
            count[j] += count[j-1];
        }

        for (int j = n-1; j >=0 ; --j) {
            int k = (a[j] / radix) % 10;
            tmp[count[k]-1] = a[j];
            count[k]--;
        }
        // 将tmp 转移到 a 中
        for (int j = 0; j < n; ++j) {
            a[j] = tmp[j];
        }
        radix *= 10;    // 进行下一个基数的比较
    }
}