//
//  main.cpp
//  DisjointSet
//
//  Created by berning on 2015/9/27.
//

#include <iostream>
using namespace std;
#include "Tools.h"
#include "DisjointSet_QuickFind.h"
#include "DisjointSet_QuickUnion.h"

#include "UnionFind.hpp"
class Student{
    int age;
    string name;
public:
    Student(string _name, int _age) : age(_age), name(_name) {}
};

void UnionFind_test() {
    UnionFind<Student*> uf;

    Student* s1 = new Student("Jack", 20);
    Student* s2 = new Student("Cube", 22);
    Student* s3 = new Student("Mark", 23);
    Student* s4 = new Student("Adas", 21);

    uf.set(s1);
    uf.set(s2);
    uf.set(s3);
    uf.set(s4);

    uf.merge(s1, s2);
    uf.merge(s3, s4);

    cout << uf.isSame(s1, s2) << endl;
    cout << uf.isSame(s3, s4) << endl;

    cout << uf.isSame(s1, s4) << endl;
    uf.merge(s1, s4);
    cout << uf.isSame(s1, s4) << endl;
}

#pragma mark - Efficiency
void timeTest(const char *name, DisjointSet *qu, int count) {
    Times::cost(name, [&]()->void{
        for (int i = 0; i < count; i++){
            qu->merge( rand() % count, rand() % count);
        }
        
        for (int i = 0; i < count; i++){
            qu->isSame( rand() % count, rand() % count);
        }
    });
}

void timeTest_DisJointSet(int count){
//    timeTest("QuickFind",  new DisjointSet_QuickFind(count), count);
//    timeTest("QuickUnion", new DisjointSet_QuickUnion(count), count);

    timeTest("QuickUnion_Size", new DisjointSet_QuickUnion_Size(count), count);
    timeTest("QuickUnion_Rank", new DisjointSet_QuickUnion_Rank(count), count);
   
    timeTest("QuickUnion_Rank_Compression", new DisjointSet_QuickUnion_Rank_Compression(count), count);
    timeTest("QuickUnion_Rank_Splitting",   new DisjointSet_QuickUnion_Rank_Splitting(count), count);
    timeTest("QuickUnion_Rank_Halving",     new DisjointSet_QuickUnion_Rank_Halving(count), count);

}
//rand()每次产生的随机数与上次是一样的，这样是为了方便程序调试；srand(seed)，不同的seed可以产生不同的随机数；
void timeTest_UnionFind(int count){
    UnionFind<int> qu;
    for (int i = 0; i < count; i++)
        qu.set(i);
    
    Times::cost("UnionFind", [&]()->void{
        for (int i = 0; i < count; i++){
            qu.merge( rand() % count, rand() % count);
        }
        
        for (int i = 0; i < count; i++){
            qu.isSame( rand() % count, rand() % count);
        }
    });
}

void test(DisjointSet* uf) {
    uf->merge(0, 1);
    uf->merge(2, 3);
    uf->merge(0, 2);

    uf->merge(4, 5);
    uf->merge(6, 7);
    uf->merge(4, 6);

    uf->merge(0, 4);
    cout << uf->isSame(0, 7) << endl;

    uf->merge(8, 9);
    uf->merge(10, 11);
    uf->merge(8, 10);

    uf->merge(12, 13);
    uf->merge(14, 15);
    uf->merge(12, 14);

    uf->merge(8, 12);
    cout << uf->isSame(8, 15) << endl;

    cout << uf->isSame(0, 8) << endl;
    uf->merge(6, 14);
    cout << uf->isSame(0, 8) << endl;
}

int main(int argc, const char * argv[]) {
    int n = 16;
    //test(new DisjointSet_QuickFind(n));

    //test(new DisjointSet_QuickUnion(n));

    //test(new DisjointSet_QuickUnion_Size(n));
    //test(new DisjointSet_QuickUnion_Rank(n));

    //test(new DisjointSet_QuickUnion_Rank_Compression(n));
    //test(new DisjointSet_QuickUnion_Rank_Splitting(n));
    //test(new DisjointSet_QuickUnion_Rank_Halving(n));


    //UnionFind_test();

    //srand((unsigned)time(nullptr));
    //int count = 10000000;
    //timeTest_DisJointSet(count);
    //timeTest_UnionFind(count);
  
    return 0;
}
