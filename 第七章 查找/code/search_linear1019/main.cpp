#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "cstring"
using namespace std;
#define MAXSIZE 100
typedef int ElemType;
// 定义块的结构
typedef struct index{
    int key;
    int start;
}index,IndexItem[3];
// 二分法查找
int Binary_Search(int L[],int key,int n);

int block_search(int key, int a[],IndexItem indexItemList);

// 排序
int cmp(const void *a,const void* b) {
    return (*(struct index*)a).key>(*(struct index*)b).key?1:-1;
}

int main() {
//// 二分查找
//    int a[MAXSIZE] = {1,3,5,7,9};
//    cout<<Binary_Search(a,5,5);
    int j = -1;
    IndexItem indexItem;
    int ab[] = {33,42,44,38,24,48, 22,12,13,8,9,20,  60,58,74,49,86,53};


    //确认模块的起始值和最大值
    for (int i=0; i<3; i++) {
        indexItem[i].start= j+1;  //确定每个块范围的起始值
        j += 6;
        for (int k=indexItem[i].start; k<=j; k++) { // 找到 范围中最大的作为key
            if (indexItem[i].key<ab[k]) {
                indexItem[i].key=ab[k];
            }
        }
    }

    //对结构体按照 key 值进行排序
    qsort(indexItem,3, sizeof(indexItem[0]), cmp);

    int key = -1,k;
    //输入要查询的数，并调用函数进行查找
    printf("请输入您想要查找的数：\n");
    cin>>key;
    k = block_search(key, ab,indexItem);
    //输出查找的结果
    if (k>0) {
        printf("查找成功！您要找的数在数组中的位置是：%d\n",k+1);
    }else{
        printf("查找失败！您要找的数不在数组中。\n");
    }

    return 0;
}

// 分块查询
int block_search(int key, int a[],IndexItem indexItemList) {
    int i;
    for (i = 0; i < 3; ++i) {
        if (key<= indexItemList[i].key)  // 如果这个key小于这个区域的最大值 则说明他在这个区域中
            break;
    }
    if (i >= 3)
        return -1; // 没有找到
    for (int j = indexItemList[i].start; j <indexItemList[i].start +6 ; ++j) {
        if (a[j] == key)
            return j;
    }
    return -1;
}

int Binary_Search(int L[],int key,int n){
    int low =0,high = n-1,mid = 0;
    while (low <= high){
        mid = (low + high) / 2;
        if (L[mid]== key){
            return mid;
        }else if (L[mid] < key){
            high = mid - 1;
        }else{
            low = mid +1;
        }
    }
    return -1;
}