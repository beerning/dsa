//
//  main.cpp
//  Backtrace
//
//  Created by berning on 2015/10/15.
//

#include <iostream>
using namespace std;
#include "queens.h"
#include "queens1.h"
#include "queens2.h"

int main(int argc, const char * argv[]) {

#ifdef _DEBUG
    //red::queens(4);
    //green::queens(4);
    blue::queens(4);

#else
    for (int i = 1; i < 11; ++i) {
        red::queens(i);
        green::queens(i);
        blue::queens(i);
        cout << endl;
    }
#endif // _DEBUG
  

    return 0;
}
