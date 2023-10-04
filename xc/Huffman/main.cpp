//
//  main.cpp
//  Huffman
//
//  Created by berning on 2015/7/20.
//

#include <iostream>
using namespace std;
#include "HuffmanTree.hpp"
#include "file.h"

void testHT(){
    const char* s = "ABBBCCCCCCCCDDDDDDEE";
    s = FILE;
    HuffmanTree ht(s);
    ht.encode(s);

    ht.printWeight();
    ht.printCodeOrder();
    ht.printCodeLevel();
    
    
    string code = ht.code();
    cout << "encode: " << endl;
    cout << code << endl;
    cout << "decode: " << endl;
    cout << ht.decode(code) << endl;
}


int main(int argc, const char * argv[]) {
    //cout << "Hello World!" << endl;
    testHT();
    //testFile4();
    
    return 0;
}
