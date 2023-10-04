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
#define FILE "F:/aberning/Documents/dev/cpp/dsa/xc/Huffman/text3.txt"
//#define FILE "F:\\aberning\\Documents\\dev\\cpp\\dsa\\xc\\Huffman\\text3.txt"
#else
#define FILE "/Users/aberning/Documents/dev/cpp/dsa/xc/Huffman/text3.txt"
#endif
void testHT(){
    const char *s = "ABBBCCCCCCCCDDDDDDEE";
    s = FILE;
    
    HuffmanTree ht(s);
//    ht.encode(s);

//    ht.printWeight();
//    ht.printCodeOrder();
    ht.printCodeLevel();


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
