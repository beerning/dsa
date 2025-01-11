
 //全排列 （permutation）

#include <stdio.h>
extern void swap(int* a, int* b);

//perm(0)
// k = 0, i = 0, i <= 2, {1, 2, 3}, perm(1)
//      k = 1, i = 1, i <= 2, {1，2, 3}, perm(2)
//              k = 2, -> 1, 2, 3
//      swap{1, 2, 3}
//      k = 1, i = 2, i <= 2, {1, 3, 2}, perm(2)
//              k = 2, -> 1, 3, 2
//      swap{1, 2, 3}
// swap{1, 2, 3}
// k = 0, i = 1, i <= 2, {2, 1, 3}, perm(1)
//      k = 1, i = 1, i <= 2, {2, 1, 3}, perm(2)
//              k = 2, -> 2, 1, 3
//      swap{2, 1, 3}
//      k = 1, i = 2, i <= 2, {2, 3, 1), perm(2)
//              k = 2, -> 2, 3, 1
//      swap{2, 1, 3}
// swap{1, 2, 3}
// k = 0, i = 2, i <= 2, {3, 2, 1}, perm(1)
//      k = 1, i = 1, i <= 2, {3, 2, 1}, perm(2)
//              k = 2, -> 3, 2, 1
//      swap{3, 2, 1}
//      k = 1, i = 2, i <= 2, {3, 1, 2}, perm(2)
//              k = 2, -> 3, 1, 2
//      swap{3, 2, 1}
// swap{1, 2, 3}
// 

/**
* int* list: The array of integers to permute.
* int k: The starting index for the permutation.
* m: The ending index for the permutation.
* n: A pointer to an integer that keeps track of the total number of permutations.
*/
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