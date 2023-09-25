//
//  TreeInfo.hpp
//  Tree
//
//  Created by berning on 2015/4/27.
//

#ifndef TreeInfo_hpp
#define TreeInfo_hpp


template<class T>
class Node;

template <class T>
class TreeInfo {
public:
    virtual Node<T> *root() const{return NULL;}
    virtual Node<T> *left(Node<T> *node) const{return NULL;}
    virtual Node<T> *right(Node<T> *node) const{return NULL;}
    virtual string description(Node<T> *node) const{return "";}
};

template <class T>
class Printer{
protected:
    TreeInfo<T> *_treeInfo;
    
public:
    Printer(TreeInfo<T> *treeInfo) : _treeInfo(treeInfo){}
    
    virtual string printString() = 0;
   
    void println() {
        print();
        cout << endl;
    }
    void print() {
        cout << printString();
    }
};

class Strings{
public:
    static string repeat(string s, int count) {
        if (s == "") return s;
        
        string builder;
        while (count-- > 0) {
            builder.append(s);
        }
        return builder;
    }
    
    static string blank(int length) {
        if (length <= 0) return "";
        string s;
        while (length-- > 0) {
            s.append(" ");
        }
        return s;
    }
};


#endif /* TreeInfo_hpp */
