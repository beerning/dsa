//开方的三种算法

#define eps 1e-7

#define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))
#define NAN        (-(float)(INFINITY * 0.0F))
#include<math.h>
//John Carmack
//InvSqrt
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
