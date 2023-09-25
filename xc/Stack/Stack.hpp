//
//  Stack.hpp
//  Stack
//
//  Created by berning on 2015/4/16.
//

#ifndef Stack_hpp
#define Stack_hpp

#include "ArrayList.hpp"

template<class T>
class Stack;

template<class T>
ostream & operator << (ostream &os, const Stack<T> &stack);

template<class T>
class Stack{
    ArrayList<T> list;
    
public:
    void push(T v);
    T    pop();
    T    top()const;
    
    int  size()const;
    bool isEmpty()const;
    void clear();
    
    friend ostream& operator<< <>(ostream &os, const Stack<T> &stack);
};

template<class T>
void Stack<T>::push(T v){
    list.add(v);
}

template<class T>
T Stack<T>::pop(){
    return list.remove(list.size() - 1);
}

template<class T>
T Stack<T>::top() const{
    return list.valueOf(list.size() - 1);
}

template<class T>
int Stack<T>::size() const{
    return list.size();
}

template<class T>
bool Stack<T>::isEmpty() const{
    return list.isEmpty();
}

template<class T>
void Stack<T>::clear(){
    list.clear();
}

template<class T>
ostream& operator<< (ostream &os, const Stack<T> &stack){
    int size = stack.size();
    
    os << "size = " << size << ", ";
    string isEmpty = stack.isEmpty() ? "YES" : "NO";
    os << "isEmpty = " << isEmpty << ", ";
    if(size)
        os << "top = " << stack.top();
    else
        os << "top = NULL";
    
    os << ", [";
    for (int i = size; i > 0; i--) {
        if (i < size) {
            os << ", ";
        }
        os << stack.list.valueOf(i - 1);
    }
    os << "]";
    
    return os;
}


#endif /* Stack_hpp */
