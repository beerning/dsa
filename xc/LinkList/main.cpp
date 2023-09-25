//
//  main.cpp
//  LinkList
//
//  Created by berning on 2015/4/13.
//

#include <iostream>
using namespace std;
#include <string>
#include "Person.h"
#include "linkedlist/linkedList.h"

template <typename List, typename T>
void print(List &list, T p4, T p8); 

void testInt(void);
void testP(void);
void testP2(void);

void testP2(void){
    cout << "---------" << __func__  << "---------" << endl;

//    SingleLinkList<Person *> list;
//    CircleSingleLinkList<Person *> list;
    
//    LinkList<Person *> list;
    
    CircleLinkList<Person *> list;
    
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

void josephus();
int main(int argc, const char * argv[]) {
    
    testInt();
    //testP();
    //testP2();
    //josephus();
    return 0;
}

template <typename List, typename T>
void print(List &list, T p4, T p8){
    cout << "add/insert: " << list << endl;
    //cout << "replace: p4(" << list.replace(p8, list.indexOf(p4)) << ") replaced by p8(" << list.valueOf(list.indexOf(p8)) <<"). " << list << endl; //p8
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

    //SingleLinkList<int> list;
    //CircleSingleLinkList<int> list;
    //LinkList<int> list;
    CircleLinkList<int> list;
    
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
    
    print(list, p4, p8);
}

void testP(void){
    cout << "---------" << __func__  << "---------" << endl;

//    SingleLinkList<Person> list;
//    CircleSingleLinkList<Person> list;
//    LinkList<Person> list;
    CircleLinkList<Person> list;

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


template<class T>
void jose(T &list, int space,  int left){
       
    cout << "Dead -> [ ";
    while (list.size() > left) {
        for (int i = 1; i < space; i++) {
            list.next();
        }
        cout << list.remove() << " ";
    }
    cout << "]" << endl;
    cout << list << " <- Left" <<  endl;
}

void josephus(){
    
    //1.
    CircleSingleLinkList<int> list1;
    for (int i = 1; i < 42; i++) {
        list1.add(i);
    }
    list1.reset();
    jose(list1, 3, 2);
    
    //2.
    CircleLinkList<int> list2;
    for (int i = 1; i < 9; i++) {
        list2.add(i);
    }
    list2.reset();
    jose(list2, 3, 1);
    
    CircleLinkList<int> list22;
    for (int i = 1; i < 9; i++) {
        list22.add(i);
    }
    list22.locate(3);
    jose(list22, 3, 1);

    
    
    //3.
    CircleLinkList<int> list3;
    for (int i = 1; i < 31; i++) {
        list3.add(i);
    }
    list3.reset();
    jose(list3, 9, 15);
        
}
