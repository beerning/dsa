#pragma once

//
//  main.cpp
//  Lambda
//
//  Created by berning on 2022/4/21.
//

/**
 *@ Description  [capture list] (params list) mutable exception-> return type { function body }
 *@ capture list     捕获外部变量列表
 *@ params list     形参列表，不能使用默认参数，不能省略参数名
 *@ mutable         用来说用是否可以修改捕获的变量
 *@ exception       异常设定
 *@ return             返回值类型
 *@ function          函数体
 *
 *有时可以省略部分结构
 *@ [capture list] (params list) -> return type {function body}
 *@ [capture list] (params list) {function body}
 *@ [capture list] {function body}
 */


namespace Lambda{
    void test1(void) { //用函数指针
        int (*p)(int, int) = [](int v1, int v2) -> int {
            return v1 + v2;
        };

        int c = p(10, 20);
        cout << c << endl;
    }

    void test2(void) {   //用函数指针
        auto p = [](int v1, int v2) {
            return v1 + v2;
        };
        int c = p(10, 20);
        cout << c << endl;
    }

    void test3(void) {
        auto p = [](int v1, int v2) {
            return v1 + v2;
        }(10, 20);

        cout << p << endl;
    }

    void test4(void) {
        auto p = [] {
            cout << "Hello World!" << endl;
        };
        p();
    }

    int exec(int a, int b, int(*p)(int, int)) {
        if (p == NULL) return 0;
        return p(a, b);
    }

    void test5(void) {
        cout << exec(20, 10, [](int v1, int v2) {return v1 + v2; }) << endl;
        cout << exec(20, 10, [](int v1, int v2) {return v1 - v2; }) << endl;
        cout << exec(20, 10, [](int v1, int v2) {return v1 * v2; }) << endl;
        cout << exec(20, 10, [](int v1, int v2) {return v1 / v2; }) << endl;
    }

#pragma mark - 捕获变量
    void test61(void) {
        int a = 10;
        int b = 20;
        auto p = [a, b] {   //值捕获
            cout << a << ", " << b << endl;
        };

        a = 11;
        b = 22;
        p();

    }

    void test62(void) {   //地址捕获
        int a = 10;
        int b = 20;
        auto p = [&a, b] {
            cout << a << ", " << b << endl;
        };
        a = 11;
        b = 22;
        p();
    }



    void test71(void) {   //隐式捕获，值捕获
        int a = 10;
        int b = 20;
        auto p = [=] {
            cout << a << ", " << b << endl;

        };
        a = 11;
        b = 22;
        p();
    }


    void test72(void) {  //隐式捕获,地址捕获
        int a = 10;
        int b = 20;
        auto p = [&] {
            cout << a << ", " << b << endl;
        };
        a = 11;
        b = 22;
        p();

    }

    void test81(void) {   //b值，其余地址捕获
        int a = 10;
        int b = 20;
        int c = 30;
        auto p = [&, b] {
            cout << a << ", " << b << ", " << c << endl;
        };
        a = 11;
        b = 22;
        c = 33;
        p();
    }


    void test82(void) {  //值捕获与地址捕获, = 必须是第一个参数(Capture default must be first)
        int a = 10;
        int b = 20;
        int c = 30;
        auto p = [=, &b] {
            cout << a << ", " << b << ", " << c << endl;
        };
        a = 11;
        b = 22;
        c = 33;
        p();
    }

    void test9(void) {   //修改外部捕获的变量
        int a = 10;
        auto p = [a]()mutable {  //mutable 前必须加（） 1.()mutable  2.->return
            cout << ++a << endl;
        };
        p();
        cout << a << endl;

    }

#pragma mark - lambda范型（C++14）
    void test10(void) {
        auto p = [](auto a, auto b) {
            return a - b;
        };

        auto c = p(20, 10);
        cout << c << endl;

    }

    //对捕获的变量初始化
    void test11(void) {
        int a = 0;
        auto p = [a = 10] {
            cout << a << endl;
        };

        p();

        cout << a << endl; //未初始化

    }

    void test() {
        test1();
    }

}


