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

#include "Person.h"

void testInt(){
    BinarySearchTree<int> bst;
    AVLTree<int> avl;

    for (int i = 1; i <= 15; i++) {
        bst.add(i);
        avl.add(i);
    }
    Tree<int>::println(bst);
    cout << endl;
    Tree<int>::println(avl);
    
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
    
    AVLTree<Person> avl([](Person p1, Person p2) -> int{
        return p1.age() - p2.age();
    });
    avl.add(p2);
    avl.add(p3);
    avl.add(p4);
    avl.add(p6);
    avl.add(p1);
    avl.add(p7);
    avl.add(p8);
    avl.add(p5);
    Tree<Person>::println(avl);
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


    AVLTree<Person *> avl([](Person *p1, Person *p2) -> int{
        return p1->age() - p2->age();
    });
    avl.add(p5);
    avl.add(p3);
    avl.add(p2);
    avl.add(p1);
    avl.add(p4);
    avl.add(p7);
    avl.add(p6);
    avl.add(p8);
    Tree<Person*>::println(avl);

}

void testString(){
    BinarySearchTree<string> bst;
    bst.add("Lury");
    bst.add("Jerry");
    bst.add("Dube");
    bst.add("Andy");
    bst.add(" ");
    Tree<string>::println(bst);

    
    AVLTree<string> avl;
    avl.add("Lury");
    avl.add("Jerry");
    avl.add("Dube");
    avl.add("Andy");
    avl.add(" ");
    
    Tree<string>::println(avl);
    
}

void testChar(){
    BinarySearchTree<const char *> bst;
    bst.add("Lury");
    bst.add("Jerry");
    bst.add("Dube");
    bst.add("Andy");
    bst.add(" ");
    Tree<const char *>::println(bst);

    
    AVLTree<const char *> avl;
    avl.add("Lury");
    avl.add("Jerry");
    avl.add("Dube");
    avl.add("Andy");
    avl.add(" ");
    
    Tree<const char *>::println(avl);
}

int main(int argc, const char * argv[]) {
    
//    testInt();
//    testP();
//    testP2();

//    testString();
    testChar();
    return 0;
}


    

