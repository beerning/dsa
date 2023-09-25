//
//  main.cpp
//  Tree
//
//  Created by berning on 2015/4/19.
//

#include <iostream>
using namespace std;
#include <string>
#include "tree/BinarySearchTree.hpp"
#include "Person.h"

void testInt(){
    BinarySearchTree<int> bst;

    bst.add(6);
    bst.add(8);
    bst.add(4);
    bst.add(7);
    bst.add(5);
    bst.add(2);
    bst.add(3);
    bst.add(1);
    bst.add(9);
    
    Tree<int>::println(bst);
    
//    bst.preOrder();
//    bst.preOrder2();
//    bst.preOrder3();
//
//    bst.inOrder();
//    bst.inOrder2();
//
//    bst.postOrder();
//    bst.postOrder2();
//
//    bst.levelOrder();
//
//    cout << "height = " << bst.height() << endl;
//    cout << "isCompelete = " << bst.isComplete() << endl;
//
//    cout << "remove(6):" << endl;
//    bst.remove(6);
//    Tree<int>::println(bst);
//        
//    cout << "contains(1) = " << bst.contains(1) << endl;
//
//    bst.clear();
//    Tree<int>::println(bst);
}

void testP(){
    BinarySearchTree<Person> bst([](Person p1, Person p2) -> int{
        return p1.age() - p2.age();
    });

    Person p1(21, "Jack");
    Person p2(22, "Lucas");
    Person p3(23, "Jerry");
    Person p4(24, "Lury");
    Person p5(25, "Bosh");
    Person p6(26, "Dube");
    Person p7(27, "Cube");
    Person p8(28, "Rose");

    bst.add(p5);
    bst.add(p3);
    bst.add(p2);
    bst.add(p1);
    bst.add(p4);
    bst.add(p7);
    bst.add(p6);
    bst.add(p8);
    Tree<Person>::println(bst);
    
    bst.preOrder();
    bst.inOrder();
    bst.postOrder();
    bst.levelOrder();
    cout << "height = " << bst.height() << endl;
    cout << "isCompelete = " << bst.isComplete() << endl;

    cout << "remove " << p5.name() << endl;
    bst.remove(p5);
    Tree<Person>::println(bst);
    
    cout << "contains(p1): " << bst.contains(p1) << endl;

    bst.clear();
    Tree<Person>::println(bst);
}

void testP2(){
    BinarySearchTree<Person *> bst([](Person *p1, Person *p2) -> int{
        return p1->age() - p2->age();
    });

    Person *p1 = new Person(21, "Jack");
    Person *p2 = new Person(22, "Lucas");
    Person *p3 = new Person(23, "Jerry");
    Person *p4 = new Person(24, "Lury");
    Person *p5 = new Person(25, "Bosh");
    Person *p6 = new Person(26, "Dube");
    Person *p7 = new Person(27, "Cube");
    Person *p8 = new Person(28, "Rose");

    bst.add(p5);
    bst.add(p3);
    bst.add(p2);
    bst.add(p1);
    bst.add(p4);
    bst.add(p7);
    bst.add(p6);
    bst.add(p8);

    Tree<Person*>::println(bst);

    bst.preOrder();
    bst.inOrder();
    bst.postOrder();
    bst.levelOrder();
    cout << "height = " << bst.height() << endl;
    cout << "isCompelete = " << bst.isComplete() << endl;

    cout << "remove " << p5->name() << endl;
    bst.remove(p5);
    Tree<Person*>::println(bst);

    cout << "contains(p1): " << bst.contains(p1) << endl;

    bst.clear();
    Tree<Person*>::println(bst);
}

void testString(){
    BinarySearchTree<string> bst;
    
    bst.add("Rose");
    bst.add("Dube");
    bst.add("Lury");
    bst.add("Bosh");
    bst.add("");
    bst.add(" ");


    
//    bst.remove("");
    Tree<string>::println(bst);
//    cout << bst << endl;
    
}

void testChar(){
    BinarySearchTree<const char *> bst;
    
    bst.add("Rose");
    bst.add("Dube");
    bst.add("Lury");
    bst.add("Bosh");
    bst.add("");
    bst.add(" ");


//    bst.remove("");
    Tree<const char *>::println(bst);
//    cout << bst << endl;
    bst.reverse();
    Tree<const char *>::println(bst);
}

int main(int argc, const char * argv[]) {
    
    //testInt();
    //testP();
    //testP2();
    
    //testString();
    testChar();
    
    return 0;
}


    

