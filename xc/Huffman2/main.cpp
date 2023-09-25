//
//  main.cpp
//  Huffman
//
//  Created by berning on 2015/7/20.
//

#include <iostream>
using namespace std;
#include "HuffmanTree.hpp"
#ifdef _WIN64
#define FILE "F:/aberning/Documents/dev/c++/dsa/xc/Huffman/text1.txt"
//#define FILE "F:\\aberning\\Documents\\dev\\c++\\dsa\\xc\\Huffman\\text2.txt"
#else
#define FILE "/Users/aberning/Documents/dev/c++/dsa/xc/Huffman/text1.txt"
#endif

void testHT(){
    const char *s = "ABBBCCCCCCCCDDDDDDEE";
    s = FILE;
    HuffmanTree ht(s);
//    ht.encode(s);

//    ht.printWeight();
//    ht.printCodeOrder();
//    ht.printCodeLevel();
    
    
    string code = ht.code();
    cout << "encode: " << endl;
    cout << code << endl;
    cout << "decode: " << endl;
    cout << ht.decode(code) << endl;
}

int main(int argc, const char * argv[]) {
    testHT();
    return 0;
}
