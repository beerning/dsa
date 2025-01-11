//
//  main.c
//  C
//
//  Created by berning on 2022/4/3.
//

#include <stdio.h>
#include <stdlib.h>

#include "_ctime.h"

extern void caizi(void);
extern void run(void);
extern void test_duplicates(void);
extern void testSqrt(void);
extern void testShuffle(void);

int main(int argc, const char * argv[]) {
    
    //caizi();
    //run();
    //test_duplicates();
    //testSqrt();
    testShuffle();
    return 0;
}
