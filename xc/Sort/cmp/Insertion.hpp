//
//  Insertion.cpp
//  Sort
//
//  Created by berning on 2015/5/7.
//

#ifndef __INSERTION_H
#define __INSERTION_H

#include <iostream>
using namespace std;

#include <vector>

#pragma mark - insert sort
void insertSort(int *a, int n){
    int v, j;
    for (int i = 1; i < n; i++){
        v = a[i];
        j = i - 1; //end of the ordered
        while (j >= 0 && v < a[j]){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = v;
    }
}

int bsearch(int* a, int idx) {
    int low = 0;
    int high = idx - 1;
    int v = a[idx];
    int mid = low;
    while (high >= low) {
        mid = low + ((high - low) >> 1);
        int x = a[mid];
        if (v < x) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

void insertSort2(int* a, int n) {//减少了比较次数，时间复杂度依然是O(n)
    int v, pos;
    for (int i = 1; i < n; i++) {
        v = a[i];
        pos = bsearch(a, i);
        for (int j = i; j > pos; j--) {
            a[j] = a[j - 1];
        }
        a[pos] = v;
    }
}

//1959 年由 唐纳德 ·希尔 （Donald Shell Shell）提出
#pragma mark - shell sort
void shellInsert(int *a, int n, int dk){
    int v, j;
    for (int i = dk; i < n; i++){
        v = a[i];
        j = i - dk;
        while (j >= 0 && v < a[j]){
            a[j + dk] = a[j];
            j -= dk;
        }
        a[j + dk] = v;
    }
}

//n/2^k
vector<int> shellSequence(int n) {//时间复杂度0(n)-O(n^2)
    vector<int> steps;
    int step = n;
    while (step >>= 1 >= 1) {
        steps.emplace_back(step);
    }
    return steps;
}
//if k is even(偶数) step = 9 * [2^k - 2^(k/2)] + 1
//if k is odd，      step = 8 * 2^k - 6 * 2^[(k + 1)/2] + 1
vector<int> sedgewickSequence(int n) {//时间复杂度0(n)-O(n^4/3)
    vector<int> steps;
    int step = 0;
    for (int k = 0; ; k++) {
        if (k % 2 == 0) {
            int x = (int)pow(2, k >> 1);
            step = 1 + 9 * (x * x - x);
        }
        else {
            int x1 = (int)pow(2, (k + 1) >> 1);
            int x2 = (int)pow(2, (k - 1) >> 1);
            step = 1 + 8 * (x1 * x2) - 6 * x1;
        }
        if (step >= n) break;
        steps.emplace(steps.begin(), step);
    }
    return steps;
}

void shellSort(int* a, int n) {
    vector<int> steps = shellSequence(n);
    steps = sedgewickSequence(n);
    for (int step : steps) {
        cout << step << ", ";
        shellInsert(a, n, step);
    }
    cout << endl;
}


//void shellSort(int *a, int n){
//    int dk = n >> 1;
//    while (dk >= 1){
//        shellInsert(a, n, dk);
//        dk >>= 1;
//    }
//}

#endif
