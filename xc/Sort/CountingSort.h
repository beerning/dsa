//
//  CountingSort.h
//  algorithm
//
//  Created by berning on 2015/9/26.
//

#ifndef CountingSort_h
#define CountingSort_h

//计数排序于 1954 年由 Harold H.Seward 提出，适合对一定范围内的整数进行排序
//核心思想： 统计每个整数在序列中出现的次，进而推导出每个整数在有序序列中的索引

/**
 * 1. 无法对负整数排序
 * 2. 极其浪费内存
 * 3. 不稳定排序
 */
void countingSort_deprecated(int *a, int n){
    int max = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] > max)
            max = a[i];
    }
    
    int size = max + 1;
    int* count = new int[size]{};
    //memset(count, 0, size * sizeof(int));
    for (int i = 0; i < n; i++){
        count[*(a + i)]++;
    }
    
    int idx = 0;
    for (int i = 0; i < size; i++){
        while(count[i]-- > 0){
            a[idx++] = i;
        }
    }
    delete[] count;
}



#pragma mark - 计数排序
void countingSort(int *a, int n){
    int max = a[0];
    int min = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    
    int k = max - min + 1;
    int* count = new int[k]{};
    for (int i = 0; i < n; i++)
        count[*(a + i) - min]++;
    
    for (int i = 1; i < k; i++)
        count[i] += count[i - 1];
    
    int* output = new int[n]{};
    for (int i = n - 1; i >= 0; i--)
        output[--count[*(a + i) - min]] = a[i];
    
    for (int i = 0; i < n; i++)
        a[i] = output[i];

    delete[] count;
    delete[] output;
}



#endif /* CountingSort_h */
