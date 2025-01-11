//数组去重

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// 过滤数组中的重复元素
int remove_duplicates(int* arr, int n) {
    if (n == 0) return 0; 

    qsort(arr, n, sizeof(int), compare);

    int unique_index = 0; // 记录不重复元素的索引

    // 遍历数组，跳过重复元素
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[unique_index]) {
            unique_index++;
            arr[unique_index] = arr[i];
        }
    }

    // 返回过滤后不重复元素的个数
    return unique_index + 1;
}

//去重2
int indexOf(int* a, int n, int value) {
    for (int i = 0; i < n; i++) {
        if (a[i] == value)
            return i;
    }
    return -1;
}

void remove_duplicates2(int* a, int n) {
    for (int i = 0; i < n; i++) {
        if (indexOf(a, n, a[i]) == i) {
            printf("%d,", a[i]);
        }
    }
    printf("\n");
}

void test_duplicates() {
    int arr[] = { 4, 2, 3, 4, 5, 1, 2, 4, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    remove_duplicates2(arr, n);
    /*

    printf("过滤后的数组元素：");
    for (int i = 0; i < new_n; i++) {
        printf("%d ", arr[i]);
    }*/
    printf("\n");
}

#include<time.h>
// 洗牌 
void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void shuffle(int* a, int n) {
    time_t t;
    srand((unsigned)time(&t));

    for (int i = n - 1; i >= 1; i--)
        swap(&a[i], &a[rand() % i]);

}

void testShuffle() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    shuffle(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}


