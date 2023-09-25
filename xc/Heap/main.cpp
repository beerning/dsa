//
//  main.cpp
//  Heap
//
//  Created by berning on 2015/7/13.
//

#include <iostream>
using namespace std;
#include "BinaryHeap.hpp"

class HeapNode{
   
public:
    HeapNode *_parent;
    HeapNode *_left;
    HeapNode *_right;
    
    HeapNode() : _parent(NULL), _left(NULL), _right(NULL) {}
    
};

using Node = HeapNode *;

void testHeap(){
    BinaryHeap<int> *heap = new BinaryHeap<int>();
    heap->add(10);
    heap->add(11);
    heap->add(12);
    heap->add(13);
    heap->add(14);
    heap->add(15);
    heap->add(16);
    heap->add(17);
    heap->add(18);
    heap->add(19);
    
    heap->add(20);
    heap->add(21);
    heap->add(22);
    heap->add(23);
    heap->add(24);
    heap->add(25);
    heap->add(26);
    heap->add(27);
    heap->add(28);
    heap->add(29);

    cout << "------------------------------add/get" << endl;
    heap->print();
    cout << "size = "<< heap->size() << endl;
    cout << "isEmpty = "<< heap->isEmpty() << endl;
    cout << "get = "<< heap->get() << endl;
    
    cout << "------------------------------remove" << endl;
    heap->remove();
    
    heap->print();
    cout << "size = "<< heap->size() << endl;
    cout << "isEmpty = "<< heap->isEmpty() << endl;
    cout << "get = "<< heap->get() << endl;
    
    cout << "------------------------------replace" << endl;
    int old = heap->replace(8);
    cout << "old = " << old << endl;
    
    heap->print();
    cout << "size = "<< heap->size() << endl;
    cout << "isEmpty = "<< heap->isEmpty() << endl;
    cout << "get = "<< heap->get() << endl;
    
    cout << "------------------------------clear" << endl;
    heap->clear();
    
    heap->print();
    cout << "size = "<< heap->size() << endl;
    cout << "isEmpty = "<< heap->isEmpty() << endl;
    cout << "get = "<< heap->get() << endl;
}

void testHeapify(){
    int a[] = {16, 2, 77, 29, 88, 19, 34, 95, 11, 64};
    vector<int> *v = new vector<int>(a, a + sizeof(a) / sizeof(int));
    cout << v->size() << endl;
   
    BinaryHeap<int> heap(v);
    heap.print();

}
int main(int argc, const char * argv[]) {
    //testHeap();
    testHeapify();
    
    


    return 0;
}
