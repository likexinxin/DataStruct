//
// Created by Dell on 2022-11-02.
//

#ifndef SORT_SWAP1102_HEAPSORT_H
#define SORT_SWAP1102_HEAPSORT_H

// 最大堆构建 升序排列
void maxHeapDown(int *a, int start, int end);
void buildMaxHeap(int *a,int n);
void heap_sortASC(int *a,int n);

//最小堆构建 降序排列
void minHeapDown(int *a,int start,int end);
void buildMinHeap(int *a,int n);
void heap_sortDES(int *a,int n);
class heapsort {

};


#endif //SORT_SWAP1102_HEAPSORT_H
