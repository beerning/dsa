//
//  main.cpp
//  Sort
//
//  Created by berning on 2015/5/7.
//

#include <iostream>
using namespace std;

#include "cmp/Insertion.hpp"
#include "cmp/Selection.hpp"
#include "cmp/Exchange.hpp"
#include "cmp/Merge.hpp"

#include "CountingSort.h"
#include "RadixSort.h"
#include "BucketSort.h"

void print(int *a, int n, const char *title){
    cout << title << ": " << "size = " << n << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}


void asort(void){
    int a[] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    //int a[] = {150, 23, 101, 3, 7, 22, 409, 30, 8, 23, 129, 3, 4, 1, 5, 12, 29, 19, 0, 2, 48, 9, 6};
    //int a[] = {41, 65, 31, 41, 19, -219, -1178, 15, -72, 11, 78, 69};
    //int a[] = { 3, 2, 6, 1, 5, 4 };

    int n = sizeof(a) / sizeof(a)[0];
    print(a, n, "origin");
      
    //insertSort(a, n);
    //insertSort2(a, n);
    //shellSort(a, n);
        
    //selectSort(a, n);
    //selectSort2(a, n);
    //heapSort(a, n);
    
    //bubbleSort(a, n);
    //bubbleSort2(a, n);
    //bubbleSort_improve1(a, n);
    //bubbleSort_improve2(a, n);
    //bubbleSort_Cocktail(a, n);
    //bubbleSort_Cocktail_i(a, n);
    //quickSort(a, 0, n - 1);
    //quickSort2(a, 0, n);
    
    /*int *temp = new int[n]();
    mergeSort(a, temp, 0, n - 1);
    cout << "temp: " << endl;
    for (int i = 0; i < n; ++i)
        cout << *(temp + i) << " ";
    cout << endl;
    delete[] temp;*/

    
    /*int *temp = new int[n >> 1]();
    mergeSort2(temp, a, 0, n);
    cout << "temp: " << endl;
    for (int i = 0; i < n >> 1; ++i)
        cout << *(temp + i) << " ";
    cout << endl;
    delete[] temp;*/
    
    //countingSort(a, n);
    //radixSort(a, n);
    //radixSort2(a, n);
    //bucketSort(a, n);
    
    sleepSort(a, n);

    print(a, n, "sorted");
    
}

int main(int argc, const char * argv[]) {

    asort();
}

