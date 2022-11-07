#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#include "sort.h"
#include "heapsort.h"
#include "merge.h"
int main() {
    int array[8] = {49,38,65,97,76,13,27,49};
    int n  = sizeof(array) / sizeof(array[0]);
//    int *result = bubble_sort(array,n);   // 冒泡排序
//    quick_sort(array,0,n-1);      // 快排
//    selectSort(array,n);        // 简单选择排序

//          堆排序
//    heap_sortASC(array,n);
//    print(array,n);
//    cout<<"升序"<<endl;
//    heap_sortDES(array,n);
//    print(array,n);
//    cout<<"降序"<<endl;

//      归并排序
//    mergeSortUp2Down(array,0,n-1);
//    mergeSortDown2Up(array,n);

//      计数排序
//    int arr[] = {1,4,1,2,5,2,4,1,8};
//    countSort(arr,n);
//    print(arr,n);
    radixSort(array,n);
    print(array,n);
    return 0;
}
