//
//  main.cpp
//  Set
//
//  Created by berning on 2015/5/23.
//

#include <iostream>
using namespace std;
#include <string>
#include "ListSet.hpp"
#include "TreeSet.hpp"

int main(int argc, const char * argv[]) {
    //ListSet<int> set;
    TreeSet<int> set;
    set.add(10);
    set.add(20);
    set.add(80);
    set.add(50);
    set.add(70);
    set.add(40);
    set.add(90);
    set.add(30);
    set.add(100);
    set.add(60);
    
    set.add(30);
    set.traversal();
    return 0;
}
