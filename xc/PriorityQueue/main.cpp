//
//  main.cpp
//  PriorityQueue
//
//  Created by berning on 2015/7/20.
//

#include <iostream>
using namespace std;
#include "PriorityQueue.hpp"

class Person{
public:
    string _name;
    int _age;
    Person(string name, int age) : _name(name), _age(age){}
    Person() : Person("", 20){}
    friend ostream & operator<< (ostream &os, const Person *p);
    
    //compare 默认按内存地址
};

ostream & operator<< (ostream &os, const Person *p){
    os << p->_name << "(" << p->_age << ")";
    return os;
}

int main(int argc, const char * argv[]) {
    
    PrioriryQueue<Person *> *pq = new PrioriryQueue<Person *>([](Person *p1, Person *p2)mutable->int{
//        return p2->_name.compare(p1->_name);  //姓名排序
        return p1->_age - p2->_age;             //年龄大者优先
    });
    pq->enQueue(new Person("Lurry", 24));
    pq->enQueue(new Person("Jackson", 18));
    pq->enQueue(new Person("Jordan", 32));
    pq->enQueue(new Person("Curry", 29));
    pq->enQueue(new Person("Rose", 17));
    pq->enQueue(new Person("Derick", 40));
    pq->enQueue(new Person("Zion", 23));
    pq->enQueue(new Person("Boldwon", 20));

    cout << pq->size() << endl;
    pq->print();
    
    while (!pq->isEmpty()){
        cout << pq->deQueue() << endl;
    }

    return 0;
}
