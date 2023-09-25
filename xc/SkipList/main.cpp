//
//  main.cpp
//  SkipList
//
//  Created by berning on 2015/10/15.
//

#include <iostream>
using namespace std;

#include "skiplist.hpp"

class Person {
public:
    int age;
};


int main(int argc, const char * argv[]) {

    skiplist<string *, int*> sklist([](string* a, string* b)->int{
            return (*a).compare(*b);
        });
    
   /* string* s1 = new string("abc");
    string* s2 = new string("adc");*/


    sklist.put(new string("aac"), new int(1));
    sklist.put(new string("abc"), new int(2));
    sklist.put(new string("acc"), new int(3));
    sklist.put(new string("adc"), new int(4));
    sklist.put(new string("aec"), new int(5));
    sklist.put(new string("afc"), new int(6));
    sklist.put(new string("bac"), new int(10));
    sklist.put(new string("bbc"), new int(20));
    sklist.put(new string("bcc"), new int(30));
    sklist.put(new string("bdc"), new int(40));
    sklist.put(new string("bec"), new int(50));
    sklist.put(new string("bfc"), new int(60));

    cout << sklist << endl;

    int *v1 = sklist.get(new string("abc"));
    cout << "get abc: " << *v1 << endl;

    int *v2 = sklist.remove(new string("adc"));
    if (v2 != nullptr) {
        cout <<"remove adc: " << *v2 << endl;
        int* v3 = sklist.get(new string("adc"));
        if (v3 == nullptr) {
            cout << "adc not exists" << endl;
         }
    }
   
    cout << endl;
    return 0;
}
