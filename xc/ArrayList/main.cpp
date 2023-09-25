//
//  main.cpp
//  ArrayList
//
//  Created by berning on 2015/4/13.
//

#include <iostream>
using namespace std;
#include <string>
#include "Person.h"
#include "ArrayList.hpp"

template <typename List, typename T>
void print(List &list, T p4, T p8);

void testInt(void);
void testP(void);
void testP2(void);

void testP2(void){
    cout << "---------" << __func__  << "---------" << endl;
    
    ArrayList<Person *> list;
    
    Person *p1 = new Person(21, "Jack");
    Person *p2 = new Person(22, "Lucas");
    Person *p3 = new Person(23, "Jerry");
    Person *p4 = new Person(24, "Lury");
    Person *p5 = new Person(25, "Bosh");
    Person *p6 = new Person(26, "Dube");
    Person *p7 = new Person(27, "Cube");
    Person *p8 = new Person(28, "Rose");
    
    cout << list << endl;
    list.add(p1);
    cout << list << endl;
    list.add(p2);
    list.add(p3);
    list.insert(p4, 0);
    list.insert(p5, 0);
    list.insert(p6, 0);
    list.insert(p7, 2);
    
    print(list, p4, p8);
}

int main(int argc, const char * argv[]) {
//
//    testInt();
//    testP();
    testP2();

    return 0;
}

template <typename List, typename T>
void print(List &list, T p4, T p8){
    cout << "add/insert: " << list << endl;
    
    //llvm 编译正确, msvc编译错误
    //cout << "replace: p4(" << list.replace(p8, list.indexOf(p4)) << ") replaced by p8(" << list.valueOf(list.indexOf(p8)) << "). " << list << endl; //p8

    //msvc按下面编译
    T pp4 = list.replace(p8, list.indexOf(p4));
    cout << "replace: p4(" << pp4 << ") replaced by p8(" << list.valueOf(list.indexOf(p8)) << "). " << list << endl; //p8
   
    cout <<"indexOf(p8) =  "<< list.indexOf(p8) << endl;
    cout << "contains(p8) = " << list.contains(p8) << endl;

    cout << "isEmpty :" << list.isEmpty() << endl;

    cout << "remove: p8(" << list.remove(list.indexOf(p8)) <<") removed. " << list << endl; //p8
    cout <<"indexOf(p8) =  "<< list.indexOf(p8) << endl;
    cout << "contains(p8) = " << list.contains(p8) << endl;

    list.clear();
    cout << "clear: "<< list << endl;
}

void testInt(void){
    cout << "---------" << __func__  << "---------" << endl;

    ArrayList<int> list;
    
    int p1 = 1;     int p2 = 2;
    int p3 = 3;    int p4 = 4;
    int p5 = 5;    int p6 = 6;
    int p7 = 7;    int p8 = 8;
    
    cout << list << endl;
    list.add(p1);
    cout << list << endl;
    list.add(p2);
    list.add(p3);
    list.insert(p4, 0);
    list.insert(p5, 0);
    list.insert(p6, 0);
    list.insert(p7, 2);  // 6, 5, 7, 4, 1, 2, 3
    
    for (int i = 0; i < 20; i++) {
        list.add(i + 100);
    }
    
    print(list, p4, p8);

}

void testP(void){
    cout << "---------" << __func__  << "---------" << endl;

    ArrayList<Person> list;

    Person p1(21, "Jack");
    Person p2(22, "Lucas");
    Person p3(23, "Jerry");
    Person p4(24, "Lury");
    Person p5(25, "Bosh");
    Person p6(26, "Dube");
    Person p7(27, "Cube");
    Person p8(28, "Rose");

    cout << list << endl;
    list.add(p1);
    cout << list << endl;
    list.add(p2);
    list.add(p3);
    list.insert(p4, 0);
    list.insert(p5, 0);
    list.insert(p6, 0);
    list.insert(p7, 2);
    
    print(list, p4, p8);

}

