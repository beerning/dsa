//
//  main.cpp
//  Recursion
//
//  Created by berning on 2015/10/15.
//

#include <iostream>
using namespace std;
#include "fibonacci.h"
#include "stair.h"
#include "hanoi.h"
#include "recursion.h"
#include "tailcall.h"


int main(int argc, const char * argv[]) {
//fib测试
    //fibPrint(fib, 10);
    //fibPrint(fib1, 10);
    //fibPrint(fib2, 10);
    //fibPrint(fib3, 10);
    //fibPrint(fib4, 10);
    //fibPrint(fib5, 10);
    //fibPrint(fib6, 10);

//爬梯子
    //fibPrint(climbStairs12, 10);
    //fibPrint(climbStairs12_12, 10);

    //fibPrint(climbStairs123, 10);
    //fibPrint(climbStairs13, 10);


//汉诺塔
    hanoi(3, "A", "B", "C");
//递归转非递归测试
    //log1(4);
    //log2(4);
    //log3(4);

//尾调用优化测试
    //test(4);
    
//尾调用消除
    //cout << factorial0(4) << endl;
    //cout << factorial1(4) << endl;

    //fibPrint(fibonacci0, 10);
    //fibPrint(fibonacci1, 10);


    return 0;
}
