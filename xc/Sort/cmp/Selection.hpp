//
//  Selection.cpp
//  Sort
//
//  Created by berning on 2015/5/7.
//JPLH-hui

#ifndef __SELECTION_H
#define __SELECTION_H

#include <iostream>
using namespace std;

//从未排序的序列中选择最小的一个元素，与当前元素交换位置
#pragma mark - select sort
void selectSort(int *a, int n){
    int min;
    for (int i = 0; i < n - 1; i++){
        min = i;
        for (int j = i + 1; j < n; j++){
            if (a[min] > a[j])
                min = j;
        }
        if(min == i) continue;
        swap(a[i], a[min]);
    }
}

void selectSort2(int *a,int n) {
    int  min ,max;
    int half = n >> 1;
    for (int i = 0; i < half; i++){
        min = i;
        max = i;
        for (int j = i + 1; j < n - i; j++){
            if (a[j] > a[max])
                max = j;
            if (a[j] < a[min])
                min = j ;
        }
        swap(a[i], a[min]);
        swap(a[n - i - 1], a[max == i ? min : max]);
    }
}


#pragma mark - heap sort
void siftDown(int *a, int n, int idx){
    int v = a[idx];
    int half = n >> 1;
    while (idx < half) {
        int cdx = (idx << 1) + 1;
        int child = a[cdx];

        int rdx = cdx + 1;
        if (rdx < n && a[rdx] > child)
            child = a[cdx = rdx];
        
        if (v >= child) break;
        a[idx] = child;
        idx = cdx;
    }
    a[idx] = v;
}
void heapSort(int *a, int n){
    for (int i = (n >> 1) - 1; i >= 0; i--)
        siftDown(a, n, i);
    
    for (int i = n - 1; i > 0; i--){
        swap(a[0], a[i]);
        siftDown(a, i, 0);
    }
}

#endif
