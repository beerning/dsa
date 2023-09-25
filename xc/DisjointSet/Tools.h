//
//  Tools.h
//  algorithm
//
//  Created by berning on 2015/9/29.
//

#ifndef Tools_h
#define Tools_h

#include <time.h>

#ifdef _WIN64
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include <math.h>
#include <functional>

class Times{
    static void printName(const char *name){
        const char *lb = "【";
        const char *rb = "】";
        size_t l1 = strlen(lb);
        size_t l2 = strlen(rb);
        size_t l3 = strlen(name);
        size_t len = l1 + l2 + l3 + 1;
        char *s = (char *)malloc(len * sizeof(char));
#ifdef _WIN64
        strcpy_s(s, len, lb);
        strcat_s(s, len, name);
        strcat_s(s, len, rb);
#else
        strcat(s, lb);
        strcat(s, name);
        strcat(s, rb);
#endif 
        cout << s << endl;
        free(s);
    }

#ifdef _WIN64
    static int gettimeofday(struct timeval* tv, struct timezone* tz) {
        SYSTEMTIME systime;
        GetLocalTime(&systime);
        tv->tv_sec = time(nullptr);
        tv->tv_usec = systime.wMilliseconds * 1000;
        return 0;
    }
#endif
public:
    
    static void cost(const char *name, function<void()> exec){
        printName(name);
       
        int m1, m2;
        time_t t1 = printTime("开始时间", m1);
        
        //执行任务
        exec();
        
        time_t t2 = printTime("结束时间", m2);
        double cost = ((t2 - t1) * 1000 + (m2 - m1)) / 1000.0;

        printf("耗时: %.3f 秒\n", cost);
        cout << "---------------------------------" << endl;
    }
    
    
    static time_t printTime(const char *s, int &milli){
        time_t stamp = time(nullptr);
        char buffer[20];
#ifdef _WIN64
        struct tm lt;
        localtime_s(&lt, &stamp);
#else
        struct tm* lt = localtime(&stamp);
#endif
        strftime(buffer, sizeof(buffer), "%X",&lt);
        
        //开始时间
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        milli = (int)round(tv.tv_usec / 1000.0);
        printf("%s: %s.%d\n", s, buffer, milli);
        return stamp;
    }
};

class Asserts_Exception : public exception{
public:
    const char * what() const noexcept override{ return "测试未通过";}
};

class Asserts {
public:
    static void test(bool value) {
        try {
            if (!value) throw new Asserts_Exception();
//            else cout << "测试通过" << endl;
        } catch (Asserts_Exception *e) {
            cout <<  e->what() << endl;
        }
    }
};

#endif /* Tools_h */
