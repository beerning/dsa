
 //全排列 （permutation）

#include <stdio.h>
extern void swap(int* a, int* b);

void perm(int* list, int k, int m, int *n) {
    if (k == m) {
        for (int i = 0; i <= m; i++)
            printf("%d ", list[i]);
        printf("\n");
        (*n)++;
    }
    else {
        for (int i = k; i <= m; i++) {
            swap(&list[k], &list[i]);
            perm(list, k + 1, m, n);
            swap(&list[k], &list[i]);
        }
    }
}

void testPerm() {
    int n = 0;
    int list[] = { 1,2,3 };
    perm(list, 0, sizeof(list) / sizeof(list[0]) - 1, &n);
    printf("total:%d\n", n);

}