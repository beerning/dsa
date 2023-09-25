//
//  testHashSet.h
//  algorithm
//
//  Created by berning on 2015/10/14.
//

#ifndef testHashSet_h
#define testHashSet_h
#include "hashCode.hpp"

class Sheep{
public:
    string name;
    int age;
    Sheep(string _name, int _age) : name(_name), age(_age) {}
    friend ostream &operator << (ostream &os, const Sheep *sheep);
};

ostream &operator << (ostream &os, const Sheep *sheep){
    return os << sheep->name << "(" << sheep->age << ")";
}

using Sheep_t = Sheep *;

#include <unordered_set>
void testHashSet(){
    bool (*equals)(Sheep_t, Sheep_t) = [](Sheep_t s1, Sheep_t s2)-> bool {
        return s1->name == s2->name && s1->age == s2->age;
    };
    
    auto hash_function = [](Sheep_t sheep)->size_t{
        return hashCode(sheep->name) * 31 + hashCode(sheep->age);
    };

    unordered_set<Sheep_t, decltype(hash_function), decltype(equals)> set(5, hash_function, equals);
    cout << "bucket_count = " << set.bucket_count() << endl;
    
    Sheep_t s1 = new Sheep("Brown", 2);
    Sheep_t s2 = new Sheep("White", 3);
    Sheep_t s3 = new Sheep("Black", 1);
    
    auto r1 = set.emplace(s1);
    auto r2 =set.emplace(s2);
    auto r3 = set.emplace(s3);
    
    Sheep_t s4 = new Sheep("Black", 1);
    auto r4 = set.emplace(s4);
    
    Sheep_t sh1 = (Sheep_t)*r1.first;
    Sheep_t sh2 = (Sheep_t)*r2.first;
    Sheep_t sh3 = (Sheep_t)*r3.first;
    Sheep_t sh4 = (Sheep_t)*r4.first;
    
    cout << "========= emplace ===========: " << endl;
    cout << "r1 -> " << sh1->name << " : " << r1.second << endl;
    cout << "r2 -> " << sh2->name << " : " << r2.second << endl;
    cout << "r3 -> " << sh3->name << " : " << r3.second << endl;
    cout << "r4 -> " << sh4->name << " : " << r4.second << endl;

    cout << "========= erase ===========: " << endl;
    cout << "erase(s1) : " << set.erase(s1) << endl;
    cout << "erase(s2) : " << set.erase(s2) << endl;
    cout << "erase(s4) : " << set.erase(s4) << endl;
    cout << "erase(s3) : " << set.erase(s3) << endl;

    cout << "========= hash ===========: " << endl;
    auto hasher = set.hash_function();
    cout << "s1->" << s1 << " : " << hasher(s1) << endl;
    cout << "s2->" << s2 << " : " << hasher(s2) << endl;
    cout << "s3->" << s3 << " : " << hasher(s3) << endl;
    cout << "s4->" << s4 << " : " << hasher(s4) << endl;


    cout << "------------" << endl;

}

void testHashMap(){
    bool (*equals)(Sheep_t, Sheep_t) = [](Sheep_t s1, Sheep_t s2)-> bool {
        return s1->name == s2->name && s1->age == s2->age;
    };
    
    auto hash_function = [](Sheep_t sheep)->size_t{
        return hashCode(sheep->name) * 31 + hashCode(sheep->age);
    };

    
    typedef unordered_map<Sheep_t, int, decltype(hash_function), decltype(equals)> HashMap;
    HashMap map(5, hash_function, equals);
    cout << "bucket_count = " << map.bucket_count() << endl;
    
    Sheep_t s1 = new Sheep("Brown", 2);
    Sheep_t s2 = new Sheep("White", 3);
    Sheep_t s3 = new Sheep("Black", 1);
    
    auto r1 = map.emplace(s1, 1);
    auto r2 = map.emplace(s2, 2);
    auto r3 = map.emplace(s3, 3);
    
    Sheep_t s4 = new Sheep("Black", 1);
    auto r4 = map.emplace(s4, 4);
        
    Sheep_t sh1 = (Sheep_t)r1.first->first;
    Sheep_t sh2 = (Sheep_t)r2.first->first;
    Sheep_t sh3 = (Sheep_t)r3.first->first;
    Sheep_t sh4 = (Sheep_t)r4.first->first;

    cout << "========= emplace ===========: " << endl;
    cout << "r1 -> " << sh1->name << " : " << r1.first->second << endl;
    cout << "r2 -> " << sh2->name << " : " << r2.first->second << endl;
    cout << "r3 -> " << sh3->name << " : " << r3.first->second << endl;
    cout << "r4 -> " << sh4->name << " : " << r4.first->second << endl;
    
    cout << "========= for_each ===========: " << endl;
    for_each(map.begin(), map.end(), [](HashMap::reference pair){
        cout << pair.first << " : " << pair.second << endl;
    });
    
    cout << "========= erase ===========: " << endl;
    cout << "erase(s1) : " << map.erase(s1) << endl;
    cout << "erase(s2) : " << map.erase(s2) << endl;
    cout << "erase(s4) : " << map.erase(s4) << endl;
    cout << "erase(s3) : " << map.erase(s3) << endl;

    cout << "========= hash ===========: " << endl;
    auto hasher = map.hash_function();
    cout << "s1->" << s1 << " : " << hasher(s1) << endl;
    cout << "s2->" << s2 << " : " << hasher(s2) << endl;
    cout << "s3->" << s3 << " : " << hasher(s3) << endl;
    cout << "s4->" << s4 << " : " << hasher(s4) << endl;

    cout << "------------" << endl;

}

void testMiniHeap(){
    Sheep_t s1 = new Sheep("Brown", 2);
    Sheep_t s2 = new Sheep("White", 3);
    Sheep_t s3 = new Sheep("Black", 4);
    Sheep_t s4 = new Sheep("Black", 1);
    Sheep_t s5 = new Sheep("Black", 5);
    Sheep_t s6 = new Sheep("Black", 6);
    Sheep_t s7 = new Sheep("Black", 7);

    unordered_set<Sheep *> vect;
    vect.emplace(s1);
    vect.emplace(s2);
    vect.emplace(s3);
    vect.emplace(s4);
    vect.emplace(s5);
    vect.emplace(s6);
    vect.emplace(s7);

    MiniHeap<Sheep_t> heap(&vect,[](Sheep_t s1, Sheep_t s2)-> int {
        return s1->age - s2->age;
    });
    heap.print();
    
    cout << heap.remove() << endl;
    heap.print();

    cout << heap.remove() << endl;
    heap.print();

    cout << heap.remove() << endl;
    heap.print();

    cout << heap.remove() << endl;
    heap.print();

}

void testLabmda() {
    int a = 10;
    int b = 20;
    EdgeInfo<int, int> e1(1001, 1002, 1000);
    EdgeInfo<int, int> e2(2001, 2002, 2000);
    
    auto p1 = [](EdgeInfo<int, int> *e1, EdgeInfo<int, int> *e2)->int{
        return e1->weight + e2->weight;
    };
    
    a = 110;
    b = 220;
    cout << p1(&e1, &e2) << endl;
    

    cout << "-----------------lambda-2-------------------" << endl;
    auto p2 = [=, &b](EdgeInfo<int, int> *e1, EdgeInfo<int, int> *e2)->int{
//        return wm->compare(e1->weight, e2->weight);
//        cout << a << endl;
        cout << a << ", " << b << endl;

        return e1->weight + e2->weight;
    };
    
    a = 110;
    b = 220;
    cout << p2(&e1, &e2) << endl;
    
    
    cout << "-----------------lambda-3-------------------" << endl;
    int(*p3)(EdgeInfo<int, int> *, EdgeInfo<int, int> *) = [](EdgeInfo<int, int> *e1, EdgeInfo<int, int> *e2)->int{
//        return wm->compare(e1->weight, e2->weight);
//        cout << a << endl;
//        cout << a << ", " << b << endl;

        return e1->weight + e2->weight;
    };
    a = 1100;
    b = 2200;
    cout << p3(&e1, &e2) << endl;
}




#endif /* testHashSet_h */
