//
//  main.cpp
//  Stack
//
//  Created by berning on 2015/4/16.
//

#include <iostream>
using namespace std;
#include <string>
#include "Person.h"
#include "Stack.hpp"

template <typename List>
void print(List &list);

void testInt(void);
void testP(void);
void testP2(void);

void testP2(void){
    cout << "---------" << __func__  << "---------" << endl;
    
    Stack<Person *> list;
    
    Person *p1 = new Person(21, "Jack");
    Person *p2 = new Person(22, "Lucas");
    Person *p3 = new Person(23, "Jerry");
    Person *p4 = new Person(24, "Lury");
    Person *p5 = new Person(25, "Bosh");
    Person *p6 = new Person(26, "Dube");
    Person *p7 = new Person(27, "Cube");
    Person *p8 = new Person(28, "Rose");
    
    cout << list << endl;
    list.push(p1);
    cout << list << endl;
    list.push(p2);
    list.push(p3);
    list.push(p4);
    list.push(p5);
    list.push(p6);
    list.push(p7);
    list.push(p8);

    print(list);
}

int main(int argc, const char * argv[]) {
    
    testInt();
    testP();
    testP2();
    return 0;
}

template <typename List>
void print(List &list){
    cout << list << endl;
    
    int size = list.size();
    for (int i = 0; i < size;  i++){
        list.pop();
        cout << "pop : "<< list << endl;
    }


    list.clear();
    cout << "clear: "<< list << endl;
}

void testInt(void){
    cout << "---------" << __func__  << "---------" << endl;

    Stack<int> list;
    
    int p1 = 1;     int p2 = 2;
    int p3 = 3;    int p4 = 4;
    int p5 = 5;    int p6 = 6;
    int p7 = 7;    int p8 = 8;
    
    cout << list << endl;
    list.push(p1);
    cout << list << endl;
    list.push(p2);
    list.push(p3);
    list.push(p4);
    list.push(p5);
    list.push(p6);
    list.push(p7);
    list.push(p8);

    print(list);

}

void testP(void){
    cout << "---------" << __func__  << "---------" << endl;

    Stack<Person> list;

    Person p1(21, "Jack");
    Person p2(22, "Lucas");
    Person p3(23, "Jerry");
    Person p4(24, "Lury");
    Person p5(25, "Bosh");
    Person p6(26, "Dube");
    Person p7(27, "Cube");
    Person p8(28, "Rose");

    cout << list << endl;
    list.push(p1);
    cout << list << endl;
    list.push(p2);
    list.push(p3);
    list.push(p4);
    list.push(p5);
    list.push(p6);
    list.push(p7);
    list.push(p8);

    print(list);

}

