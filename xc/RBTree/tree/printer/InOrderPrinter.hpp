//
//  InOrderPrinter.hpp
//  Tree
//
//  Created by berning on 2015/4/27.
//

#ifndef InOrderPrinter_hpp
#define InOrderPrinter_hpp

#include "TreeInfo.hpp"

template <class T>
class InorderPrinter : public Printer<T>{
    string rightAppend;
    string leftAppend;
    string blankAppend;
    string lineAppend;
    unsigned count;
    string printString(Node<T> *node, string nodePrefix, string leftPrefix,string rightPrefix);
public:
    InorderPrinter(TreeInfo<T> *treeInfo) : Printer<T>(treeInfo){
        count = 0;
        int length = 2;
        rightAppend = "┌" + Strings::repeat("─", length);
        leftAppend = "└" + Strings::repeat("─", length);
        blankAppend = Strings::blank(length + 1);
        lineAppend = "│" + Strings::blank(length);
    }
    
    string printString() {
        string s = printString(this->_treeInfo->root(), "", "", "");
        s.erase(s.length() - 1, 1);
        return "size = " + to_string(count) + "\n" + s;
    }
};

template<class T>
string InorderPrinter<T>::printString(Node<T> *node,string nodePrefix,string leftPrefix,string rightPrefix) {
    count++;
    TreeInfo<T> *treeInfo = this->_treeInfo;
    
    Node<T> *left = treeInfo->left(node);
    Node<T> *right = treeInfo->right(node);
    string desc = treeInfo->description(node);
    
    int length = (int)desc.length();
    if (length % 2 == 0) {
        length--;
    }
    length >>= 1;
    
    string nodeString = "";
    if (right != NULL) {
        rightPrefix += Strings::blank(length);
        nodeString += printString(right,
                rightPrefix + rightAppend,
                rightPrefix + lineAppend,
                rightPrefix + blankAppend);
    }
    nodeString += nodePrefix + desc + "\n";
    if (left != NULL) {
        leftPrefix += Strings::blank(length);
        nodeString += printString(left,
                leftPrefix + leftAppend,
                leftPrefix + blankAppend,
                leftPrefix + lineAppend);
    }
    return nodeString;
}

#endif /* InOrderPrinter_hpp */
