//
//  QuickSort.cpp
//  Sort
//
//  Created by berning on 2015/5/7.
//

#ifndef __EXCHANGE_H
#define __EXCHANGE_H

#include <iostream>
using namespace std;

#pragma mark - bubble sort
void bubbleSort(int *a, int n){
    for(int i = 1 ; i < n; i++){
        for(int j = 0; j < n - i; j++){
            if(a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        }
    }
}

void bubbleSort2(int *a, int n){
    int i = 1;
    while (i < n){
        for (int j = 0; j < n - i; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
        i++;
    }
}

void bubbleSort_improve1(int *a, int n){
    int i = n - 1;
    while (i > 0){
        bool sorted = true;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]){
                sorted = false;
                swap(a[j], a[j + 1]);
            }
        }
        if (sorted) break;
        i--;
    }
}

void bubbleSort_improve2(int *a, int n){
    int i = n - 1;
    while (i > 0){
        int pos = 0;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                pos = j;
                swap(a[j], a[j + 1]);
            }
        }
        i = pos;
    }
}

void bubbleSort_Cocktail(int *a, int n){
    int low = 0;
    int high = n - 1;
    while (low < high){
        for (int i = low; i < high; ++i)
            if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        --high;
        
        for (int i = high; i > low; --i)
            if (a[i] < a[i - 1]) swap(a[i], a[i - 1]);
        ++low;
    }
}

void bubbleSort_Cocktail_i(int *a, int n){
    int low = 0;
    int high = n - 1;
    while (low < high){
        bool sorted = true;
        for (int i = low; i < high; ++i)
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                sorted = false;
            }
        if (sorted) break;
        --high;
        for (int i = high; i > low; --i)
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
                sorted = false;
            }
        if (sorted) break;
        ++low;
    }
}
//1960年由 查尔斯·安东尼·理查德 ·霍尔（ Charles Antony Richard Hoare Hoare，缩写为 C.A.R.Hoare Hoare）提出
#pragma mark - quick sort
int partition(int *a, int low, int high){
    int pivot = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivot)
            high--;
        swap(a[low], a[high]);
        while (low < high && a[low] <= pivot)
            low++;
        swap(a[low], a[high]);
    }
    cout << low << ":" << a[low] << endl;
    return low;
}

//int partition(std::vector<int>& nums, int low, int high) {
//    int pivot = nums[high];  // 选择最后一个元素作为基准
//    int i = low - 1;  // i是较小元素的索引
//
//    for (int j = low; j < high; ++j) {
//        if (nums[j] < pivot) {
//            ++i;  // 增加较小元素的索引
//            std::swap(nums[i], nums[j]);
//        }
//    }
//    std::swap(nums[i + 1], nums[high]);
//    return i + 1;
//}

void quickSort(int *a, int low, int high){
    if (low >= high) return;
    int pivot = partition(a, low, high);
    quickSort(a, low, pivot - 1);
    quickSort(a, pivot + 1, high);
}

void quickSort2(int* a, int low, int high) {
    if (low + 1 >= high) return;
    int pivot = partition(a, low, high - 1);
    quickSort2(a, low, pivot);
    quickSort2(a, pivot + 1, high);
}


#endif
