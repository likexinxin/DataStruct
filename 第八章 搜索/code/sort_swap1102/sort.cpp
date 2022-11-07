//
// Created by Dell on 2022-11-02.
//

#include "sort.h"
//
// Created by Dell on 2022-11-02.
//
#include "stdio.h"
#include <iostream>
using namespace std;


void swap(int *a,int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;

}
//  ---------------------------交换排序-----------------
/**
 * 以降序的形式 进行排序
 * @param a 数组
 * @param n 数组长度
 * @return 排序好的数组
 */
int* bubble_sort(int a[],int n){
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (a[i] < a[j])
                swap(&a[i],&a[j]);
        }
    }

    return a;
}

/**
 *  快速排序
 * @param a 待排数组
 * @param l 左边的下标 (例如，从起始位置开始排序，则l=0)
 * @param r 右边的下标  (例如，排序截至到数组末尾，则r=a.length-1)
 */
void quick_sort(int *a,int l,int r){
    if (l < r){
        int i = l;
        int j = r;
        int x = a[l]; // 基准
        while (i<j){
            while (i<j && a[j]>=x)  // 先从左往右寻找第一个小于X的数
                j--;
            a[i] = a[j];
            while (i<j && a[i]<=x)
                i++;
            a[j] = a[i];
        }
        a[i] = x;
        quick_sort(a,l,i-1);
        quick_sort(a,i+1,r);
    }
}

// ----------------------------分界线----------------------------------------

//----------------------选择排序--------------------------------------------
/**
 * 简单选择排序
 * @param a 数组
 * @param n 数组长度
 */
void selectSort(int *a,int n){
    int min=0;
    for (int i = 0; i < n-1; ++i) {
        min = i;
        for (int j = i+1; j < n; ++j) {
            if (a[j] < a[min])
                min = j;
        }
        if (min != i)
            swap(a[i],a[min]);
    }
}




void print(int a[],int n){
    for (int i = 0; i < n; ++i) {
        cout<<a[i]<<"  ";
    }
}

