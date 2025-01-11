//
//  main.cpp
//  B-Tree
//
//  Created by berning on 2015/5/13.
//

#include <iostream>
using namespace std;

#include "BTree.hpp"
#include "Tools.h"

void testEff(){
    BTree<int> bt(300);
    int count = 10000000;
    Times::cost("BTree", [&]{
        for (int i = 0; i < count; i++){
            bt.add(i);
        }
        cout << "height = " << bt.height() << endl;
    });
}

void testInt(){
    BTree<int> bt(4);
    bt.add(10);
    bt.add(20);
    bt.add(16);
    bt.add(60);
    bt.add(15);
    bt.add(19);
    bt.add(65);
    bt.add(54);
    bt.add(23);
    bt.add(31);
    bt.add(32);
    bt.add(18);
    bt.add(40);
    bt.add(41);
    bt.add(42);
    
    bt.add(10);
    
    bt.remove(15);
    bt.remove(23);
    bt.remove(41);
    cout << bt << endl;
    
//    cout << "height = " << bt.height() << endl;
//    cout << bt.contains(19) << endl;
    
    //1.del directly
//    bt.remove(18);
    
    //2.borrow from left
//    bt.remove(31);
    
    //3.borrow from right
//    bt.remove(10);
    
    //4.merge
    bt.remove(40);  //merge with right
    cout << bt << endl;

    bt.remove(54); //1.del directly
    cout << bt << endl;
    bt.remove(65);  //merge with left and parent underflow(borrow from left)
    cout << bt << endl;

    bt.remove(42);  //1.del directly
    cout << bt << endl;
    
    bt.remove(60);  //merge with left and parent underflow(merge with left and up to root)
    
    cout << bt << endl;

}



int main(int argc, const char * argv[]) {
    
    //testInt();
//    BTree<int> bt;
//    for (int i = 0; i < 100; i++){
//        bt.add(i);
//    }
//
//    cout << bt << endl;
//    cout << "contains 67 : "<< bt.contains(67) << endl;
//
//
//    for (int i = 50; i < 100; i++){
//        bt.remove(i);
//    }
//
//    cout << bt << endl;
//    cout << "contains 67 : " << bt.contains(67) << endl;

    
    testEff();
    return 0;
}
