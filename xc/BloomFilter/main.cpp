//
//  main.cpp
//  BloomFilter
//
//  Created by berning on 2015/10/15.
//

#include <iostream>
using namespace std;
#include "bloomfilter.hpp"
#include <unordered_map>
int main(int argc, const char* argv[]) {
   
    int n = 1000000;
    boomfilter<string> bm(n, 0.01);
    for (int i = 1; i <= n; i++) {
        bm.put(to_string(i));
    }

    int count = 0;
    for (int i = n + 1 ; i <= n * 2; i++) {
        if (bm.contains(to_string(i)))
            count++;
    }

    bm.print();

    cout << "count = " << count << endl;


    return 0;
}


