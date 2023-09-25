//
//  leetcode_60.h
//  algorithm
//
//  Created by berning on 2015/7/27.
//

#ifndef leetcode_60_h
#define leetcode_60_h

#include <cmath>
//69平方根Sqrt(x)
int sqrtByNewton(int n){
    if (n < 0)return NAN;
    if (n == 0) return 0;
    double val = n; //先猜想一个值，即猜想val为n
    double last;
    do{
        last = val;
        val = (val + n / val) * 0.5;
    }while(fabs(val - last) > 1e-16);
    return (int)val;
}

double sqrtByBisection(int n) {
    if (n < 0) return NAN;
    if (n == 0) return 0;
    double low = 0;
    double high = n;
    double mid = low + (high - low) * 0.5;
    double last;
    do{
       if (mid * mid > n) high = mid;
       else if (mid * mid < n) low = mid;
       else break;
       
       last = mid;
       mid = low + (high - low) * 0.5;
    }while(fabs(last - mid) > 1e-16);
    return mid;
}


void test60(){
    printf("sqrtByNewton = %d\n", sqrtByNewton(36));
    printf("sqrtByBisection = %f\n", sqrtByBisection(36));

}

#endif /* leetcode_60_h */
