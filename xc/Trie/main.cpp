//
//  main.cpp
//  Trie
//
//  Created by berning on 2015/7/20.
//

#include <iostream>
using namespace std;
#include "Trie.hpp"

void testTrie(){
    Trie t;
    t.add("add");
    t.add("address");
    t.add("good");
    t.add("addidas");
    t.add("addition");
    t.add("subway");
    t.add("sub");
    t.add("goodness");
    t.add("add");
    t.add("good");
    t.add("sub");
    t.add("list");

//    t.remove("addition");
//    t.clear();
    cout << "size = " << t.size() << endl;
    cout << "isEmpty = " << t.isEmpty() << endl;

    cout << "contains(goo): " << t.contains("goo") << endl;
    cout << "has(goo): " << t.has("goo") << endl;

}


int main(int argc, const char * argv[]) {
    testTrie();
    return 0;
}
