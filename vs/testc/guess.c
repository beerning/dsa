//
//  guess.c
//  C
//
//  Created by berning on 2022/4/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void caizi(void);

void go_on(char begin){
    if (begin == 'Y' || begin == 'y'){//重复玩的一个嵌套循环
        caizi();
    }
    else{
        printf_s("谢谢，再见!\n");
    }

}

void print(const char* s1, const char* s2) {
    char begin;
    printf_s(s1);
    getchar();
    printf_s(s2);
    scanf_s("%c", &begin);
    go_on(begin);
}

void caizi(void){
    int n;
    int count = 1;
    srand((int)time(NULL));
    int m = (rand() % 100) + 1;

    puts("游戏开始，请输入数字:");
    const char* s = "需要挑战最高级别不？Y/N \n ";
    while (1){
        scanf_s("%d", &n);
        if (n == m) {
            printf_s("猜中了，使用了 %d 次！\n", count);
            if (count == 1){
                print("你是神级人物了！膜拜\n", "你已经达到最高级别，还需要玩吗？Y/N \n");
            } 
            else if (count <= 5){
                print("你是王级人物了！非常赞\n", s);
            }
            else if (count <= 10){
                print("你是大师级人物了！狂赞\n", s);
            }
            else if (count <= 15){
                print("你是钻石级人物了！怒赞\n", s);
            }
            else{
                printf_s("", "你的技术还有待提高哦！重玩？ Y / N\n");
            }
            break;
        }
        else if (n < m){
            puts("太小了!重新输入:");
        }
        else{
            puts("太大了!重新输入:");
        }
        count++;//计数器
        
    }
}
 
