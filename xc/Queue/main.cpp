//
//  main.cpp
//  Queue
//
//  Created by berning on 2015/4/17.
//

#include <iostream>
using namespace std;
#include <string>
#include "Person.h"
#include "queue/queue.h"

template <typename List>
void printQueue(List &list);

void testQueueInt(void);
void testQueueP(void);
void testQueueP2(void);

template <typename List>
void printDeque(List &list);
void testDequeInt(void);
void testDequeP(void);
void testDequeP2(void);

void testQ(void){
    testQueueInt();
    //testQueueP();
    //testQueueP2();
}

void testDq(void){
    testDequeInt();
    testDequeP();
    testDequeP2();
}

int main(int argc, const char * argv[]) {
    testQ();
        
    //testDq();
    
    return 0;
}

#pragma mark - queue

template <typename List>
void printQueue(List &list){
    cout << list << endl;
    
    int size = list.size();
    for (int i = 0; i < size;  i++){

        cout << "deQueue(" << list.deQueue() << "): " << list << endl;
    }
    
    list.clear();
    cout << "clear: "<< list << endl;
}

void testQueueInt(void){
    cout << "---------" << __func__  << "---------" << endl;
    Queue<int> list;
    //CircleQueue<int> list;

    int p1 = 1;     int p2 = 2;
    int p3 = 3;    int p4 = 4;
    int p5 = 5;    int p6 = 6;
    int p7 = 7;    int p8 = 8;

    cout << list << endl;
    list.enQueue(p1);
    cout << list << endl;
    list.enQueue(p2);
    list.enQueue(p3);
    list.enQueue(p4);
    list.enQueue(p5);
    list.enQueue(p6);
    list.enQueue(p7);
    list.enQueue(p8);
    
    cout << list << endl;

    cout << "deQueue(" << list.deQueue() << "): " << list << endl;
    cout << "deQueue(" << list.deQueue() << "): " << list << endl;

    for (int i = 20; i < 30; i++) {
        list.enQueue(i);
    }
    
    printQueue(list);
}

void testQueueP(){
    cout << "---------" << __func__  << "---------" << endl;
        //Queue<Person> list;
    CircleQueue<Person> list;
    
    Person p1(21, "Jack");
    Person p2(22, "Lucas");
    Person p3(23, "Jerry");
    Person p4(24, "Lury");
    Person p5(25, "Bosh");
    Person p6(26, "Dube");
    Person p7(27, "Cube");
    Person p8(28, "Rose");

    cout << list << endl;
    list.enQueue(p1);
    cout << list << endl;
    list.enQueue(p2);
    list.enQueue(p3);
    list.enQueue(p4);
    list.enQueue(p5);
    list.enQueue(p6);
    list.enQueue(p7);
    list.enQueue(p8);
    
    printQueue(list);

}

void testQueueP2(void){
    cout << "---------" << __func__  << "---------" << endl;
   
    //Queue<Person *> list;
    CircleQueue<Person *> list;
    
    Person *p1 = new Person(21, "Jack");
    Person *p2 = new Person(22, "Lucas");
    Person *p3 = new Person(23, "Jerry");
    Person *p4 = new Person(24, "Lury");
    Person *p5 = new Person(25, "Bosh");
    Person *p6 = new Person(26, "Dube");
    Person *p7 = new Person(27, "Cube");
    Person *p8 = new Person(28, "Rose");
    
    cout << list << endl;
    list.enQueue(p1);
    cout << list << endl;
    list.enQueue(p2);
    list.enQueue(p3);
    list.enQueue(p4);
    list.enQueue(p5);
    list.enQueue(p6);
    list.enQueue(p7);
    list.enQueue(p8);
    
    printQueue(list);
}



#pragma mark - deque
template <typename List>
void printDeque(List &list){
    cout << list << endl;
    
    int size = list.size();
    for (int i = 0; i < size;  i++){

        if (i % 2) {
            cout << "deQueueFront(" << list.deQueueFront() << "): " << list << endl;

        }else{
            cout << "deQueueRear(" << list.deQueueRear()<< "): " << list << endl;
        }
    }
    
    list.clear();
    cout << "clear: "<< list << endl;
}



void testDequeInt(void){
    cout << "---------" << __func__  << "---------" << endl;
    Deque<int> list;
    //CircleDeque<int> list;

    int p1 = 1;     int p2 = 2;
    int p3 = 3;    int p4 = 4;
    int p5 = 5;    int p6 = 6;
    int p7 = 7;    int p8 = 8;
    
    cout << list << endl;
    list.enQueueRear(p1);
    cout << list << endl;
    list.enQueueFront(p2);
    list.enQueueFront(p3);
    list.enQueueRear(p4);
    list.enQueueRear(p5);
    list.enQueueFront(p6);
    list.enQueueRear(p7);
    list.enQueueRear(p8); //6, 3, 2, 1, 4, 5, 7, 8
    
    cout << list << endl;
    for (int i = 20; i < 30; i+=2) {
        list.enQueueRear(i);
    }

    for (int i = 20; i < 30; i+=2) {
        list.enQueueFront(i + 1);
    }

    printDeque(list);
    
}




void testDequeP(void){
    cout << "---------" << __func__  << "---------" << endl;
    Deque<Person> list;
    //CircleDeque<Person> list;
    
    Person p1(21, "Jack");
    Person p2(22, "Lucas");
    Person p3(23, "Jerry");
    Person p4(24, "Lury");
    Person p5(25, "Bosh");
    Person p6(26, "Dube");
    Person p7(27, "Cube");
    Person p8(28, "Rose");

    cout << list << endl;
    list.enQueueRear(p1);
    cout << list << endl;
    list.enQueueFront(p2);
    list.enQueueFront(p3);
    list.enQueueRear(p4);
    list.enQueueRear(p5);
    list.enQueueFront(p6);
    list.enQueueRear(p7);
    list.enQueueRear(p8);

    printDeque(list);

}

void testDequeP2(void){
    cout << "---------" << __func__  << "---------" << endl;
    
    Deque<Person *> list;
    //CircleDeque<Person *> list;

    Person *p1 = new Person(21, "Jack");
    Person *p2 = new Person(22, "Lucas");
    Person *p3 = new Person(23, "Jerry");
    Person *p4 = new Person(24, "Lury");
    Person *p5 = new Person(25, "Bosh");
    Person *p6 = new Person(26, "Dube");
    Person *p7 = new Person(27, "Cube");
    Person *p8 = new Person(28, "Rose");


    cout << list << endl;
    list.enQueueRear(p1);
    cout << list << endl;
    list.enQueueFront(p2);
    list.enQueueFront(p3);
    list.enQueueRear(p4);
    list.enQueueRear(p5);
    list.enQueueFront(p6);
    list.enQueueRear(p7);
    list.enQueueRear(p8);
    
    printDeque(list);
}




