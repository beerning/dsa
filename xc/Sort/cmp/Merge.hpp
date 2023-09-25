//
//  Merge.hpp
//  Sort
//
//  Created by berning on 2015/8/5.
//

#ifndef Merge_hpp
#define Merge_hpp

#include <iostream>
using namespace std;

//1945 年由 约翰 ·冯·诺伊曼（ John von Neumann Neumann）首次提出 
//核心思想：
//① 不断地将当前序列平均分割成 2个子序列，直到不能再分割（序列中只剩 1个元素）
//② 不断地将 2个子序列合并成一个有序序列，直到最终只剩下 1个有序列


//将 [begin, mid] 和 [mid, end] 范围的序列合并成一个有序序列
//void merge(int *src,int *temp, int begin, int mid, int end){
//    int i = begin, j = mid + 1, k = begin;
//    while(i != mid + 1 && j != end + 1){
//        if(src[i] > src[j])
//            temp[k++] = src[j++];
//        else
//            temp[k++] = src[i++];
//    }
//    while(i != mid + 1)
//        temp[k++] = src[i++];
//    while(j != end + 1)
//        temp[k++] = src[j++];
//    for(i = begin; i <= end; i++)
//        src[i] = temp[i];
//}

void merge(int* src, int* temp, int begin, int mid, int end) {
    int i = begin, j = mid + 1, k = begin;
    while (i <= mid && j <= end) {
        if (src[i] > src[j])
            temp[k++] = src[j++];
        else
            temp[k++] = src[i++];
    }
    while (i <= mid)
        temp[k++] = src[i++];
    while (j <= end)
        temp[k++] = src[j++];
    for (i = begin; i <= end; i++)
        src[i] = temp[i];
}

// 对 [begin, end] 范围的数据进行归并排序
void mergeSort(int *src, int *temp, int begin, int end){
    if (begin >= end) return;
    int mid = begin + ((end - begin) >> 1);
    mergeSort(src, temp, begin, mid);
    mergeSort(src, temp, mid + 1, end);
    merge(src, temp, begin, mid, end);
}

#pragma mark - mergeSort2
/**
 * 将 [begin, mid) 和 [mid, end) 范围的序列合并成一个有序序列
 */
void merge2(int *leftArray, int *array, int begin, int mid, int end) {
    int li = 0, le = mid - begin;
    int ri = mid, re = end;
    int ai = begin;
    
    // 备份左边数组
    for (int i = li; i < le; i++) {
        leftArray[i] = array[begin + i];
    }
    
    // 如果左边还没有结束
    while (li < le) {
        if (ri < re && array[ri] < leftArray[li]) {
            array[ai++] = array[ri++];
        } else {
            array[ai++] = leftArray[li++];
        }
    }
}

// T(n) = T(n/2) + T(n/2) + O(n)
/**
 * 对 [begin, end) 范围的数据进行归并排序
 */
void mergeSort2(int *leftArray, int *array, int begin, int end) {
    if (begin + 1 >= end) return;
    
    int mid = begin + ((end - begin) >> 1);
    mergeSort2(leftArray, array, begin, mid);
    mergeSort2(leftArray, array, mid, end);
    merge2(leftArray, array, begin, mid, end);
}


#endif /* Merge_hpp */
