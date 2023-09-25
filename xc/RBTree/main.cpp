//
//  main.cpp
//  Tree
//
//  Created by berning on 2015/4/19.
//

#include <iostream>
using namespace std;
#include <string>
#include "tree/AVLTree.hpp"
#include "tree/RBTree.hpp"
#include "Person.h"

#include "Tools.h"

void testInt(){
    
    int p1 = 21, p2 = 22, p3 = 23, p4 = 24, p5 = 25, p6= 26, p7 =27, p8 = 28;

    BinarySearchTree<int> bst;
    bst.add(p2);
    bst.add(p3);
    bst.add(p4);
    bst.add(p6);
    bst.add(p1);
    bst.add(p7);
    bst.add(p8);
    bst.add(p5);

    RBTree<int> rb;
    rb.add(p2);
    rb.add(p3);
    rb.add(p4);
    rb.add(p6);
    rb.add(p1);
    rb.add(p7);
    rb.add(p8);
    rb.add(p5);


    Tree<int>::println(bst);
    cout << endl;
    Tree<int>::println(rb);
//    rb.reverse();
//    Tree<int>::println(rb);
}

void testP(){
    Person p1(21, "Jack");
    Person p2(22, "Lucas");
    Person p3(23, "Jerry");
    Person p4(24, "Lury");
    Person p5(25, "Bosh");
    Person p6(26, "Dube");
    Person p7(27, "Cube");
    Person p8(28, "Rose");
    
    BinarySearchTree<Person> bst([](Person p1, Person p2) -> int{
        return p1.age() - p2.age();
    });
    
    bst.add(p2);
    bst.add(p3);
    bst.add(p4);
    bst.add(p6);
    bst.add(p1);
    bst.add(p7);
    bst.add(p8);
    bst.add(p5);
    Tree<Person>::println(bst);
    
    RBTree<Person> rb([](Person p1, Person p2) -> int{
        return p1.age() - p2.age();
    });
    
    rb.add(p2);
    rb.add(p3);
    rb.add(p4);
    rb.add(p6);
    rb.add(p1);
    rb.add(p7);
    rb.add(p8);
    rb.add(p5);
    Tree<Person>::println(rb);
}

void testP2(){
    Person *p1 = new Person(21, "Jack");
    Person *p2 = new Person(22, "Lucas");
    Person *p3 = new Person(23, "Jerry");
    Person *p4 = new Person(24, "Lury");
    Person *p5 = new Person(25, "Bosh");
    Person *p6 = new Person(26, "Dube");
    Person *p7 = new Person(27, "Cube");
    Person *p8 = new Person(28, "Rose");
    
    BinarySearchTree<Person*> bst([](Person* p1, Person* p2) -> int{
        return p1->age() - p2->age();
    });
    
    bst.add(p2);
    bst.add(p3);
    bst.add(p4);
    bst.add(p6);
    bst.add(p1);
    bst.add(p7);
    bst.add(p8);
    bst.add(p5);
    Tree<Person*>::println(bst);


    RBTree<Person *> rb([](Person *p1, Person *p2) -> int{
        return p1->age() - p2->age();
    });
    rb.add(p2);
    rb.add(p3);
    rb.add(p4);
    rb.add(p6);
    rb.add(p1);
    rb.add(p7);
    rb.add(p8);
    rb.add(p5);
    Tree<Person*>::println(rb);

}

void testString(){
    BinarySearchTree<string> bst;
    bst.add("Lury");
    bst.add("Jerry");
    bst.add("Dube");
    bst.add("Andy");
    bst.add(" ");
    Tree<string>::println(bst);

    
    RBTree<string> rb;
    rb.add("Lury");
    rb.add("Jerry");
    rb.add("Dube");
    rb.add("Andy");
    rb.add(" ");
    
    Tree<string>::println(rb);
    
}

void testChar(){
    BinarySearchTree<const char *> bst;
    bst.add("Lury");
    bst.add("Jerry");
    bst.add("Dube");
    bst.add("Andy");
    bst.add(" ");
    Tree<const char *>::println(bst);

    
    RBTree<const char *> rb;
    rb.add("Lury");
    rb.add("Jerry");
    rb.add("Dube");
    rb.add("Andy");
    rb.add(" ");

    Tree<const char *>::println(rb);
}


void timeCost(const char *name, BinarySearchTree<int> *t, int count){
    Times::cost(name, [&]() -> void{
        for (int i = 1; i < count; i++){
            t->add(i);
        }
        cout << "height = " << t->height() << endl;
    });
}

void timeTest(){
    int count = 1000000;
//    timeCost("BST", new BinarySearchTree<int>, count);
    timeCost("AVLTree", new AVLTree<int>, count);
    timeCost("RBTree", new RBTree<int>, count);
}


int main(int argc, const char * argv[]) {
    
    testInt();
//    testP();
//    testP2();
//    testString();
    //testChar();
    
    //timeTest();
    return 0;
}