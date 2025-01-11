#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>

// 分割线函数
void printDivider(char symbol, int length, const char *title) {
    if (title != NULL) length = length / 2 -  strlen(title) / 2;
    for (int i = 0; i < length; i++) {
        printf("%c", symbol);
    }
    if (title != NULL) printf("%s", title);
    for (int i = 0; i < length; i++) {
        printf("%c", symbol);
    }
    printf("\n\n");
}

// 打印数组函数
void printArray(int arr[], int n, bool isCRLF) {
    for (int i = 0; i < n; i++) {
        if (arr[i] < 10) {
            printf("0%d ", arr[i]);
        }
        else {
            printf("%d ", arr[i]);
        }
    }
    if (isCRLF == true)
        printf("\n\n");
    else{
        printf("+ ");
    }
        
}

// 插入排序函数
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i]; // 取出当前待插入的元素
        j = i - 1;

        // 将比key大的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // 插入key到正确的位置
    }
}

// 清零函数
void zeroArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 0; // 将每个元素设置为0
    }
}

// 数组拷贝函数
void arrayCopy(const int *src, int *dest, int size) {
    if(size == 0) return;
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

bool contains(int *a, int n, int num) {
    while(n-- > 0) {
        if (num == *a)
            return true;
        a++;
    }
    return false;
}

void handle_error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void generate(int n, int *userRed, int *userBlue, int rs, int bs, int *factor, int n1, int n2, int rmax, int bmax) {
    
    /* 初始化随机数发生器 */
    time_t t;
    srand((unsigned) time(&t));
  
    int num, round = 0;
   
    const int red = n1;
    const int blue = n2;

    int* a = malloc(red * sizeof(int));
    if (a == NULL) handle_error("内存分配失败");
    ;

    int* b = malloc(blue * sizeof(int));
    if (b == NULL) handle_error("内存分配失败");
   
    int* f = factor += rs;
    
    while (round < n) {
        zeroArray(a, red);
        zeroArray(b, blue);
        arrayCopy(userRed, a, rs);
        arrayCopy(userBlue, b, bs);
        
        //red
        for (int i = rs; i < red; i++) {
            num = rand() % rmax + 1;

            while (contains(a, red, num) == true) {
                num = (*factor * num + rmax / 2) % rmax + 1;
            }

            if(a) a[i] = num;
            factor++;
        }
        insertionSort(a, red);
        printArray(a, red, false);

        //blue
        for(int i = bs; i < blue; i++) {
            num = rand() % bmax + 1;

            while (contains(b, blue, num) == true) {
                num = (*factor * num + bmax / 2) % bmax + 1;;
            }
            if (b) b[i] = num;
            factor++;
        }
        insertionSort(b, blue);
        printArray(b, blue, true);
       
        //next series
        round++;
        factor = f;;
      
        //printDivider('-', 46);

    }
    free(a);
    free(b);
}

void lottery(int n) {

#define LOTTER_RED      5
#define LOTTER_BLUE     2
#define LOTTER_RED_MAX  35
#define LOTTER_BLUE_MAX 12

    int factor[] = {7, 9, 10, 5, 8, 4, 2};
    
    int rs = 0;
    int bs = 0;
    int red[] = { 11, 22, 30 };
    int blue[] = { 10 };

    if (true) rs = sizeof(red) / sizeof(red[0]);
    if (false)  bs = sizeof(blue) / sizeof(blue[0]);
    generate(n, red, blue, rs, bs, factor, LOTTER_RED, LOTTER_BLUE, LOTTER_RED_MAX, LOTTER_BLUE_MAX);
}

void double_color(int n) {
#define DOUBLE_COLOR_RED        6
#define DOUBLE_COLOR_BLUE       1
#define DOUBLE_COLOR_RED_MAX    33
#define DOUBLE_COLOR_BLUE_MAX   16
    int factor[] = {1, 2, 5, 16, 28, 30, 12};
    
    int rs = 0;
    int bs = 0;
    int red[] = { 2, 16, 30 };
    int blue[] = { 4 };

    if (true) rs = sizeof(red) / sizeof(red[0]);
    if (false)  bs = sizeof(blue) / sizeof(blue[0]);
    generate(n, red, blue, rs, bs, factor, DOUBLE_COLOR_RED, DOUBLE_COLOR_BLUE, DOUBLE_COLOR_RED_MAX, DOUBLE_COLOR_BLUE_MAX);

}

void gennumber(int n, int k) {
    time_t t;
    srand((unsigned)time(&t));

    int bits = k;
    int round = 0;
    while (round < n) {
        while(k > 0) {
            printf("%d ", rand() % 10);
            k--;
        }
        printf("\n");
        round++;
        k = bits;
    }
}

void rank3d(int n) {
    gennumber(n, 3);
}

void rank5(int n) {
    gennumber(n, 5);
}

void run()
{
    int n = 5;
    printDivider('=', 46, "大乐透");
    lottery(n);
    
    printDivider('=', 46, "双色球");
    double_color(n);
    
    printDivider('=', 46, "3D");
    rank3d(n);
    
    printDivider('=', 46, "排列三");
    rank3d(n);
    
    printDivider('=', 46, "排列五");
    rank5(n);
}
