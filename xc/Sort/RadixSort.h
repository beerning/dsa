//
//  RadixSort.h
//  algorithm
//
//  Created by berning on 2015/9/27.
//

#ifndef RadixSort_h
#define RadixSort_h

void counting_sort(int *a, int n, int divisor, int k, int low, int loop, int *count, int *output){
    memset(count, 0, k * sizeof(int));
    for (int i = 0; i < n; i++)
        count[*(a + i) / divisor % loop - low]++;

    for (int i = 1; i < k; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--)
        output[--count[*(a + i) / divisor % loop - low]] = a[i];

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}

void radixSort(int *a, int n){
    int max = a[0];
    int min = a[0];
    for (int i = 1; i < n; i++){
        if (max < a[i]) max = a[i];
        if (min > a[i]) min = a[i];
    }
    max = abs(max) >= abs(min) ? abs(max) : abs(min);

    int loop = 10;
    int low = -9;
    int k = (loop << 1) - 1;
    int* count = new int[k] {};
    int* output = new int[n] {};

    for (int divisor = 1; divisor <= max; divisor *= loop) {
        counting_sort(a, n, divisor, k, low, loop, count, output);
    }
}

#pragma mark - RadixSort2
void radixSort2(int *a, int n){
    int max = a[0];
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (max < a[i]) max = a[i];
        if (min > a[i]) min = a[i];
    }
    max = abs(max) >= abs(min) ? abs(max) : abs(min);
    
    int loop = 10;
    int low = -9;
    int k = (loop << 1) - 1;
    int **buckets = new int*[k];

    for (int i = 0; i < k; i++)
        buckets[i] = new int[n]{};

    int* bucketSize = new int[k]{};
    for (int divisor = 1; divisor <= max; divisor *= loop){
        for (int i = 0; i < n; i++){
            int no = a[i] / divisor % loop - low;
            buckets[no][bucketSize[no]++] = a[i];
        }
                
        int idx = 0;
        for (int i = 0; i < k; i++) {    
            for (int j = 0; j < bucketSize[i]; j++) {
                a[idx++] = buckets[i][j];
            }
            bucketSize[i] = 0;
        }
    }
}




#endif /* RadixSort_h */
