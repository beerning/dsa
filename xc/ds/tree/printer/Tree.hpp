//
//  Tree.hpp
//  Tree
//
//  Created by berning on 2015/4/27.
//

#ifndef Tree_hpp
#define Tree_hpp

#include "InOrderPrinter.hpp"
#include "LevelOrderPrinter.hpp"

typedef enum : int{
    LEVEL_ORDER,
    IN_ORDER
}PrintStyle;

template <class T>
class Tree{

    static Printer<T>* printer(TreeInfo<T> &tree, PrintStyle style) {
        if (style == IN_ORDER)
            return new InorderPrinter<T>(&tree);
        return new LevelOrderPrinter<T>(&tree);
    }
public:
    static void print(TreeInfo<T> &tree) { print(tree, LEVEL_ORDER);}
    static void println(TreeInfo<T> &tree) {println(tree, LEVEL_ORDER);}
    static string printString(TreeInfo<T> &tree) {return printString(tree, LEVEL_ORDER);}

    static void print(TreeInfo<T> &tree, PrintStyle style) {
        if (tree.root() == NULL) return;
        printer(tree, style)->print();
    }
    static void println(TreeInfo<T> &tree, PrintStyle style) {
        if (tree.root() == NULL) return;
        
        printer(tree, style)->println();
    }
    static string printString(TreeInfo<T> &tree, PrintStyle style) {
        if (tree.root() == NULL) return NULL;
        return printer(tree, style)->printString();
    }
        
};

#endif /* Tree_hpp */
