//
//  BucketSort.h
//  algorithm
//
//  Created by berning on 2015/9/27.
//

#ifndef BucketSort_h
#define BucketSort_h

void insert(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        int v = a[i];
        int j = i;
        while (j > 0 && v < a[j - 1]) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

void bucketSort(int *a, int n){
    int max = a[0];
    int min = a[0];
    for (int i = 0; i < n; i++){
        if (max < a[i]) max = a[i];
        if (min > a[i]) min = a[i];
    }
   
    int capacity = 10;
    int minBucket = min / capacity;
    int maxBucket = max / capacity;
    int k = maxBucket - minBucket + 1;
    int** buckets = new int* [k] {};
    for (int i = 0; i < k; i++)
        buckets[i] = nullptr;
    int* bucketSize = new int[k] {};
   
    for (int i = 0; i < n; i++){
        int no = a[i] / capacity - minBucket;
        int *bucket = buckets[no];
        if (bucket == nullptr){
            bucket = new int[n]{};
            buckets[no] = bucket;
        }
        bucket[bucketSize[no]++] = a[i];
    }
    
    int idx = 0;
    for (int i = 0; i < k; i++){
        int *bucket = buckets[i];
        if (bucket == nullptr) continue;
        insert(bucket, bucketSize[i]);
        
        for (int j = 0; j < bucketSize[i]; j++)
            a[idx++] = bucket[j];
    }
}


#ifdef _WIN64
#include <thread> 
#include <chrono> 
#else
#include <unistd.h>
#endif

int idx = 0;
void pause_thread(int *a, int v) {
    this_thread::sleep_for(chrono::seconds(v));
    cout << v << " ";
    a[idx++] = v;
}

void sleepSort(int *a, int n){
    vector<thread> threads;
    int* temp = new int[n] {};

    for (int i = 0; i < n; i++) {
        threads.emplace_back(thread(pause_thread, temp, a[i]));
    }
    for (auto &t : threads) {
        t.join();
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }
    delete[] temp;
}

#endif /* BucketSort_h */
