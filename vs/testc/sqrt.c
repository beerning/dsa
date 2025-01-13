//开方的三种算法

#define eps 1e-7

//#define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
//#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))
//#define NAN        (-(float)(INFINITY * 0.0F))
#include<math.h>
//John Carmack
//思想：快逆平方根算法（一种计算1/sqrt(x)的高效计算技术）
//方法：1. 该算法首先将浮点数 x 的位模式解释为一个整数
//      2. 使用一个魔数 0x5f3759df，结合 x 的位移整数表示，生成 1/sqrt(x)的初始猜测
//      3. 牛顿-拉夫森迭代（Newton-Raphson Iteration), 利用y = 1 / sqrt(x)构建原函数， 即f(y) = 1 / pow(y, 2) - x, 
//      y = 1 / sqrt(x)
// 
//      导数f(y)` = -2 / pow(y, 3), 
//      y[n+1] = y[n] - f(y[n]) / f(y[n])` 
//             = y[n](1.5 - 0.5 * x * pow(y[n], 2)
//

float sqrtByCarmack(float x) {
    if (x < 0)return NAN;
    if (x == 0) return 0;

    float xhalf = 0.5f * x;
    int i = *(int*)&x; // get bits for floating VALUE
    i = 0x5f375a86 - (i >> 1); // gives initial guess y0
    
    x = *(float*)&i; // convert bits BACK to float
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

    return 1 / x;
}

//   x[n+1] = x[n] - f(x[n]) / f(x[n])` 
//   f(x) = pow(x, 2) - a
//   f(x)`= 2x
//   x[n+1] = x[n] - (pow(x, 2) - a) / 2x 
//          = x[n] - x[n] / 2 + a/2x
//          = x[n]/2 + a/2x
//          = 1/2 (x[n] + a/x)
//

float sqrtByNewton(float n) {
    if (n < 0)return NAN;
    
    float val = n; //先猜想一个值，即猜想val为n
    float last;
    do {
        last = val;
        val = (val + n / val) * 0.5;
    } while (fabsf(val - last) > eps);
    return val;
}

//二分法
float sqrtByBisection(float n) {
    if (n < 0)return NAN;

    float mid, last;
    float low = 0, high = n;

    mid = (low + high) * 0.5;
    do {
        if (mid * mid > n)
            high = mid;
        else if (mid * mid < n)
            low = mid;
        else
            break;
        last = mid;
        mid = (low + high) * 0.5;
    } while (fabsf(mid - last) > eps);
    return mid;
}

void testSqrt(){
    float n = 2.f;

    printf("sqrtByCarmack: %f 的开方为： %f\n", n, sqrtByCarmack(n));
    printf("sqrtByNewton: %f 的开方为： %f\n", n, sqrtByNewton(n));
    printf("sqrtByBisection: %f 的开方为： %f\n", n, sqrtByBisection(n));

}
