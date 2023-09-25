#pragma once
//
//  main.cpp
//  Exception
//
//  Created by berning on 2022/4/21.
//

namespace Exception {
    int divide1(int a, int b) {
        if (b == 0) throw "除数不能为0...";
        return a / b;
    }

    void test1(void) {
        try {
            int a = 10;
            int b = 0;
            int c = divide1(a, b);
            cout << c << endl;
        }
        catch (const char* exception) {
            cout << exception << endl;
        }
    }

#pragma mark - 自定义异常

    class Exception {
    public:
        virtual string what() const noexcept = 0;
    };

    class DevideException : public Exception {
    public:
        string what() const noexcept { return "除数不能为0..."; }
    };

    int divide2(int a, int b) {
        if (b == 0) throw DevideException();
        return a / b;
    }


    void test2(void) {
        try {
            int a = 10;
            int b = 0;
            int c = divide2(a, b);
            cout << c << endl;
        }
        catch (const Exception& e) {
            cout << e.what() << endl;
        }
    }

#pragma mark - 继承标准库异常
    class DebugException : public exception {
    public:
        const char* what() const noexcept { return "数组越界了...";; };
    };

    void test3(void) {
        try {
            throw DebugException();
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    }


    void outBounds(int idx) throw() {
        try {
            if (idx > 5)
                throw "数组越界了...";
        }
        catch (const char* e) {
            cout << e << endl;
        }

    }

    void test() {
        test1();
    }
}
