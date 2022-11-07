#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void print(int a[],int n,int i);    // 自定义输出函数
void InsertSort(int a[],int n);     // 直接插入函数
void binary_insertSort(int a[],int n);  //折半插入排序
void shell_sort(int a[],int n);    // 第一种希尔排序
int main() {
    int a[8] = {3,1,7,5,2,4,9,6};
    int n = sizeof(a)/ sizeof(a[0]);
//    cout<<"-----------直接插入算法---------------"<<endl;
//    InsertSort(a, n);

//    cout<<"-------------折半插入排序-------------"<<endl;
//    binary_insertSort(a,n);

    cout<<"-------------希尔排序--------------"<<endl;
    shell_sort(a,n);
    return 0;
}

/**
 *
 * @param a :数组
 * @param n ： 数组长度
 * @param i ： 第i次 排序
 */
void print(int a[],int n,int i){
    cout<<i<<" : ";
    for (int j = 0; j < n; ++j) {
        cout<<a[j];
    }
    cout<<endl;
}

/**
 * 直接插入排序
 * @param a 数组
 * @param n 数组长度
 */
void InsertSort(int a[],int n){
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i-1]){ // 若后面这个元素< 前面这个元素 ，就要去前面找到属于他的位置
            int j =i-1;
            int x = a[i];
            // 退出条件 ：1.找到了尽头 也就是 x 比 a[0]还要小，比完之后 j = 0 -1 = -1；
            //              so exit 条件之一： j>-1
            //          2.前面这个数已经比 x 小了
            while (j>-1 && x < a[j]){
                a[j+1] = a[j];   // 前面的到后面去
                j--;
            }
            a[j+1] = x; // 找到位置了
        }
        print(a,n,i);
    }
}

/**
 * 折半插入排序
 * @param a 数组
 * @param n 数组长度
 */
void binary_insertSort(int a[],int n){
    int low,high,mid,x = 0;
    for (int i = 1; i <n ; ++i) {
        low = 0;
        high = i-1;
        x = a[i];
        while (low <= high){
            mid = (low + high)/ 2;
            if (x < a[mid]){
                high = mid-1;
            }else{
                low = mid +1;
            }
        }
        for (int j = i; j >low ; --j) {
            a[j] = a[j-1];
        }
        a[low] = x;
        print(a,n,i);
    }
}

/**
 * 希尔排序
 * @param a 数组
 * @param n 数组长度
 */
void shell_sort(int a[],int n){
    for (int gap = n/2; gap > 0 ; gap/=2) {
        cout<<"gap为："<<gap<<endl;
        // gap个组 进行分组
        for (int i = 0; i < gap; ++i) {
            for (int j = i+gap; j <n ;  j += gap) {
                // 直接插入排序
                if (a[j] <a[j -gap]){
                    int x = a[j];
                    int k = j;
                    while (k>=0 && x < a[k]){
                        a[k+gap] = a[k];    // 前一个元素到后面去
                        k = k - gap;    // k 前移
                    }
                    a[k+gap] = x;
                }
            }
        }
    }
}