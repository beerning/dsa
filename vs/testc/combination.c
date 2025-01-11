
#include <stdio.h>
#include <stdlib.h>
//组合 （combination）
// 
//
// comb(0, 0)
// idx = 0, begin = 0, j = 0, j <= 1, C[0] = A[0] = 1, comb(1, 1)         
//      idx = 1, begin = 1, j = 1, j <= 2, C[1] = A[1] = 2, comb(2, 2)
//              idx = 2, begin = 2, j = 2, j <= 3, C[2] = A[2] = 3, comb(3, 3), return; 1,2,3
//              idx = 2, begin = 2, j = 3, j <= 3, C[2] = A[3] = 4, comb(3, 4), return; 1,2,4
// 
//      idx = 1, begin = 1, j = 2, j <= 2, C[1] = A[2] = 3, comb(2, 3)
//              idx = 2, begin = 3, j = 3, j <= 3  C[2] = A[3] = 4, comb(3, 4), return; 1,3,4
// 
// idx = 0, begin = 0, j = 1, j <= 1, C[0] = A[1} = 2, comb(1, 2)
//      idx = 1, begin = 2, j = 2, j <= 2, C[1] = A[2] = 3, comb(2, 3)
//              idx = 2, begin = 3, j = 3, j <= 3, C[2] = A[3] = 4, comb(3, 4), return; 2,3,4

void combination(int index, int begin, int n, int m, int* A, int* C, int *count) {
    if (index == m) {
        for (int i = 0; i < m; i++)
            printf("%d ", C[i]);
        printf("\n");
        (*count)++;
        return;
    }
    for (int j = begin; j <= n - m + index; j++) {
        C[index] = A[j];
        combination(index + 1, j + 1, n, m, A, C, count);
    }
}

void testComb() {
    int count = 0;

    int A[] = { 1,2,3,4 };
    int m = 3;
    int* C = (int*)malloc(m * sizeof(int));
    combination(0, 0, sizeof(A) / sizeof(A)[0], m, A, C, &count);
    printf("total:%d\n", count);
    free(C);
}

