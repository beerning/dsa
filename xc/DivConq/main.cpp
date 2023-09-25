//
//  main.cpp
//  DivConq
//
//  Created by berning on 2015/10/15.
//

#include <iostream>
using namespace std;
#include "max_subArray.h"
#include "quicksort.h"
#include "mergesort.h"

int main(int argc, const char* argv[]) {
    //最大连续子序列和
        max_continous_subarray();

//快速排序
   /* int a[] = { 9, 4, 1, 8, 3, 6, 5, 7, 2 };
    size_t n = sizeof(a) / sizeof(int);
    arraytraversal(a, n, "origin");

    quicksort(a, 0, n);
    arraytraversal(a, n, "quicksort");*/
//归并排序
    //int* output = new int[n / 2]{};
    //mergesort(a, output, 0, n);
    //arraytraversal(a, n, "mergesort");

//shuffle
    /*for (int i = 0; i < 20; ++i) {
        shuffle1(a, n);
        arraytraversal(a, n);
        quicksort(a, 0, n);
    }*/
     


    return 0;
}
