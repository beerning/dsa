//
//  LevelOrderPrinter.hpp
//  Tree
//
//  Created by berning on 2015/4/27.
//

#ifndef LevelOrderPrinter_hpp
#define LevelOrderPrinter_hpp

#include "TreeInfo.hpp"
#include <vector>
#include <queue>

template<class T>
class Nodebox;

template <class T>
class LevelOrderPrinter : public Printer<T>{
    static const int MIN_SPACE;
    Nodebox<T> *_root;
    int _minX;
    int _maxWidth;
    Node<T> *leftChild(Node<T> *node){return this->_treeInfo->left(node);}
    Node<T> *rightChild(Node<T> *node){return this->_treeInfo->right(node);}

    using LList = vector<vector<Nodebox<T> *>>;
    using List = vector<Nodebox<T> *>;

    Nodebox<T>* addNodebox(List &boxes, Node<T>* node);
public:
    LevelOrderPrinter(TreeInfo<T> *treeInfo) : Printer<T>(treeInfo){
        _root = new Nodebox<T>(treeInfo->root(), treeInfo);
        _maxWidth = _root->_width;
    }
    
    string printString() override;
    void fillNodes(LList &boxes);
    void cleanNodes(LList &boxes);
    void compressNodes(LList &boxes);
    
    void addXLineNode(List &rowBoxes, Nodebox<T> *parent, int x);
    Nodebox<T> * addLineNode(List &rowBoxes, List &nextRow, Nodebox<T> *parent, Nodebox<T> *child);
    void addLineNodes(LList &boxes);
};

template<class T>
const int LevelOrderPrinter<T>::MIN_SPACE = 1;

template<class T>
string LevelOrderPrinter<T>::printString(){
    LList boxes;
    
    fillNodes(boxes);
    cleanNodes(boxes);
    compressNodes(boxes);
    addLineNodes(boxes);

    int rows = boxes.size();
    string s;
    for (int i = 0; i < rows; i++) {
        if (i != 0) s.append("\n");
        List rowBoxes = boxes.at(i);
        
        string rowString;
        int rowSize = rowBoxes.size();
        int length = 0;
        int leftSpace = 0;
        for (int j = 0; j < rowSize; j++) {
            Nodebox<T> *box = rowBoxes.at(j);
           
            length += leftSpace;
            leftSpace = box->_x - length - _minX;
            
            rowString.append(Strings::blank(leftSpace));
            rowString.append(box->_desc);

            length += box->_width;
        }
        s.append(rowString);
    }
    return s;
}

template<class T>
Nodebox<T>* LevelOrderPrinter<T>::addNodebox(List &rowBoxes, Node<T>* node){
    Nodebox<T>* box = NULL;
    if (node) {
        box = new Nodebox<T>(node, this->_treeInfo);
        _maxWidth = max(_maxWidth, box->_width);
        rowBoxes.emplace_back(box);
    } else {
        rowBoxes.emplace_back(nullptr);
    }
    return box;
}

template<class T>
void LevelOrderPrinter<T>::fillNodes(LList &boxes){//根据二叉树节点设置box的父子信息；若节点不存在，用NULL填充（目的是在cleanNode函数中计算box的坐标，计算完删掉）
    List firstRow;
    firstRow.emplace_back(_root);
    boxes.emplace_back(firstRow);
    
    while (true) {
        List preRow = boxes.at(boxes.size() - 1);
        List rowBoxes;

        bool notNull = false;
        int preRowSize = preRow.size();
        for (int i = 0; i < preRowSize; i++){
            Nodebox<T> *box = preRow.at(i);
            
            if (!box) {
                rowBoxes.emplace_back(nullptr);
                rowBoxes.emplace_back(nullptr);
            } else {
                Nodebox<T> *left = addNodebox(rowBoxes, leftChild(box->_node));
                if (left) {
                    box->_left = left;
                    left->_parent = box;
                    notNull = true;
                }

                Nodebox<T> *right = addNodebox(rowBoxes, rightChild(box->_node));
                if (right) {
                    box->_right = right;
                    right->_parent = box;
                    notNull = true;
                }
            }
        }
        // 全是null，就退出
        if (!notNull) break;
        boxes.emplace_back(rowBoxes);
    }
}

template<class T>
void LevelOrderPrinter<T>::cleanNodes(LList &boxes){//设置box的坐标，并从行数组中清除空节点
    int rows = boxes.size();
    if (rows < 2) return;

    int lastRowSize = boxes.at(rows - 1).size();
    int boxSpace = _maxWidth;
    int lastRowLength = lastRowSize * _maxWidth + boxSpace * (lastRowSize - 1);

    for (int i = 0; i < rows; i++) {
        List rowBoxes = boxes.at(i);
        int rowSize = rowBoxes.size();
        
        int rowSpace = lastRowLength - (rowSize - 1) * boxSpace;
        int cornerSpace = rowSpace / rowSize - _maxWidth;
        cornerSpace >>= 1;

        int rowX = 0;
        vector<int> idxes; //记录空节点
        for (int j = 0; j < rowSize; j++) {
            if (j != 0) { rowX += boxSpace;}
            rowX += cornerSpace; //左边
            Nodebox<T> *box = rowBoxes.at(j);
            if (box) {
                // 居中（由于奇偶数的问题，可能有1个符号的误差）
                int deltaX = (_maxWidth - box->_width) >> 1;
                box->_x = rowX + deltaX;
                box->_y = i;
            }
            else {
                idxes.emplace(idxes.begin(), j);
            }
            rowX += _maxWidth;
            rowX += cornerSpace; //右边
        }
        // 删除所有的null
        for (int i = 0; i < idxes.size(); i++) {
            rowBoxes.erase(rowBoxes.begin() + idxes.at(i));
        }
        boxes.at(i) = rowBoxes;
    }
}

template<class T>
void LevelOrderPrinter<T>::compressNodes(LList &boxes){
    int rows = boxes.size();

    for (int i = rows - 2; i >= 0; i--) {
        List rowBoxes = boxes.at(i);
        
        for (int j = 0; j < rowBoxes.size(); j++){
            Nodebox<T> * box = rowBoxes.at(j);
            
            Nodebox<T> *left = box->_left; 
            Nodebox<T> *right = box->_right;
            if (!left && !right) continue;
            if (left  && right ) {
                // 让左右节点对称
                box->balance(left, right);

                // left和right之间可以挪动的最小间距
                int leftEmpty = box->leftBoundEmptyLength();
                int rightEmpty = box->rightBoundEmptyLength();
                int empty = min(leftEmpty, rightEmpty);
                empty = min(empty, (right->_x - left->rightX()) >> 1);

                // left、right的子节点之间可以挪动的最小间距
                int space = (int)left->minLevelSpaceToRight(right) - MIN_SPACE;
                space = min(space >> 1, empty);

                // left、right往中间挪动
                if (space > 0) {
                    left->translateX(space);
                    right->translateX(-space);
                }
                // 继续挪动
                space = (int)left->minLevelSpaceToRight(right) - MIN_SPACE;
                if (space < 1) continue;

                // 可以继续挪动的间距
                leftEmpty = box->leftBoundEmptyLength();
                rightEmpty = box->rightBoundEmptyLength();
                if (leftEmpty < 1 && rightEmpty < 1) continue;

                if (leftEmpty > rightEmpty) {
                    left->translateX(min(leftEmpty, space));
                } else {
                    right->translateX(-min(rightEmpty, space));
                }
            } else if (left) {
                left->translateX(box->leftBoundEmptyLength());
            } else { // right != null
                right->translateX(-box->rightBoundEmptyLength());
            }
        }
    }
}
   
template<class T>
void LevelOrderPrinter<T>::addXLineNode(List &rowBoxes, Nodebox<T> *parent, int x){
    Nodebox<T> *line = new Nodebox<T>("─");
    line->_x = x;
    line->_y = parent->_y;
    rowBoxes.emplace_back(line);
}

template<class T>
Nodebox<T>* LevelOrderPrinter<T>::addLineNode(List &rowBoxes, List &nextRow, Nodebox<T> *parent,  Nodebox<T> *child) {
    if (!child) return NULL;

    Nodebox<T> *top = NULL;
    int topX = child->topLineX();
    if (child == parent->_left) {
        top = new Nodebox<T>("┌");
        rowBoxes.emplace_back(top);
        
        for (int x = topX + 1; x < parent->_x; x++) {
            addXLineNode(rowBoxes, parent, x);
        }
    } else {
        for (int x = parent->rightX(); x < topX; x++) {
            addXLineNode(rowBoxes, parent, x);
        }
        top = new Nodebox<T>("┐");
        rowBoxes.emplace_back(top);
    }

    // 坐标
    top->_x = topX;
    top->_y = parent->_y;
    child->_y = parent->_y + 2;
    _minX = min(_minX, child->_x);

    // 竖线
    Nodebox<T> *bottom = new Nodebox<T>("│");
    bottom->_x = topX;
    bottom->_y = parent->_y + 1;
    nextRow.emplace_back(bottom);
    
    return top;
}

template<class T>
void LevelOrderPrinter<T>::addLineNodes(LList &boxes){
    int rows = boxes.size();
    
    LList tempBoxes;
    _minX = _root->_x;

    for (int i = 0; i < rows; i++) {
        List rowBoxes = boxes.at(i);
        if (i == rows - 1) {
            tempBoxes.emplace_back(rowBoxes);
            continue;
        }
        
        List tempRowBoxes;
        List nextRowBoxes;
        for (int j = 0; j < rowBoxes.size(); j++){
            Nodebox<T> * box = rowBoxes.at(j);
            addLineNode(tempRowBoxes, nextRowBoxes, box, box->_left);
            tempRowBoxes.emplace_back(box);
            addLineNode(tempRowBoxes, nextRowBoxes, box, box->_right);
        }
        tempBoxes.emplace_back(tempRowBoxes);
        tempBoxes.emplace_back(nextRowBoxes);
    }
    
    boxes.clear();
    for (int i = 0; i < tempBoxes.size(); i++){
        List list = tempBoxes.at(i);
        boxes.emplace_back(list);
    }
}


#pragma mark -
template<class T>
class LevelInfo {
public:
    int _leftX;
    int _rightX;
    LevelInfo(Nodebox<T> *left, Nodebox<T> * right) {
        _leftX = left->leftBound();
        _rightX = right->rightBound();
    }
};

template<class T> class Nodebox;
template<class T> ostream & operator<<(ostream &os, const Nodebox<T> *box);
template<class T>
class Nodebox{
    static const int TOP_LINE_SPACE;
    void init(string s); 

public:
    Node<T> *_node;
    Nodebox *_left;
    Nodebox *_right;
    Nodebox *_parent;

    int _x;
    int _y;
    int _treeHeight;
    string _desc;
    int _width;
    
    Nodebox(string s);
    Nodebox(Node<T> *node, TreeInfo<T> *treeInfo);
    
    int rightX()const;
    void translateX(int deltaX);
    
    int topLineX() const;
    
    int leftBound() const;
    int rightBound() const;
        
    int leftBoundLength() const;
    int rightBoundLength() const;
    
    int leftBoundEmptyLength() const;
    int rightBoundEmptyLength() const;
    void balance(Nodebox *left, Nodebox *right) const;

    int treeHeight(Nodebox *box) const;
    long minLevelSpaceToRight(Nodebox *right) const;
    LevelInfo<T>* levelInfo(int level) const;
    
    friend ostream & operator<< <>(ostream &os, const Nodebox<T> *box);
};

template<class T>
const int Nodebox<T>::TOP_LINE_SPACE = 1;

template<class T>
void Nodebox<T>::init(string s){
    int length = (int)s.length();
    if (s == "┌" || s == "┐" || s == "│" || s == "─") length = 1;

    _x = 0;
    _y = 0;
    _treeHeight = 0;
    _left = NULL;
    _right = NULL;
    _parent = NULL;
    _node = NULL;
    
    _desc = s.empty() ? " " : s;
    _width = length;
}

#pragma mark - Public
template<class T>
Nodebox<T>::Nodebox(string s){
   init(s);
}
template<class T>
Nodebox<T>::Nodebox(Node<T> *node, TreeInfo<T> *treeInfo){
   init(treeInfo->description(node));
   _node = node;
}

template<class T>
int Nodebox<T>::rightX() const{
    return _x + _width;
}

template<class T>
void Nodebox<T>::translateX(int deltaX){
    if (deltaX == 0) return;
    _x += deltaX;

    if (!_node) return;
     
    if (_left) {
        _left->translateX(deltaX);
    }
    if (_right) {
        _right->translateX(deltaX);
    }
}

template<class T>
int Nodebox<T>::topLineX() const{
    int delta = _width;
    if (delta % 2 == 0) {
        delta--;
    }
    delta >>= 1;

    if (_parent && this == _parent->_left) {
        return rightX() - 1 - delta;
    } else {
        return _x + delta;
    }
    //return _x + (_width >> 1);
}

template<class T>
int Nodebox<T>::leftBound() const{
    if (!_left) return _x;
    return _left->topLineX();
}

template<class T>
int Nodebox<T>::rightBound() const{
    if (!_right) return rightX();
    return _right->topLineX() + 1;
}

template<class T>
int Nodebox<T>::leftBoundLength() const{
    return _x - leftBound();
}

template<class T>
int Nodebox<T>::rightBoundLength() const{
    return rightBound() - rightX();
}

template<class T>
int Nodebox<T>::leftBoundEmptyLength() const{
    return leftBoundLength() - 1 - TOP_LINE_SPACE;
}

template<class T>
int Nodebox<T>::rightBoundEmptyLength() const {
    return rightBoundLength() - 1 - TOP_LINE_SPACE;
}

template<class T>
void Nodebox<T>::balance(Nodebox<T> *left, Nodebox<T> *right) const{
    if (!left || !right ) return;
    
    int deltaLeft = _x - left->rightX();
    int deltaRight = right->_x - rightX();

    int delta = max(deltaLeft, deltaRight);
    int newRightX = rightX() + delta;
    right->translateX(newRightX - right->_x);

    int newLeftX = _x - delta - left->_width;
    left->translateX(newLeftX - left->_x);
}

template<class T>
int Nodebox<T>::treeHeight(Nodebox<T> *box) const{
    if (!box) return 0;
    if (box->_treeHeight) return box->_treeHeight;
    box->_treeHeight = 1 + max(treeHeight(box->_left), treeHeight(box->_right));
    return box->_treeHeight;
}

template<class T>
long Nodebox<T>::minLevelSpaceToRight(Nodebox<T> *right) const{
    int thisHeight = treeHeight((Nodebox<T> *)this);
    int rightHeight = treeHeight(right);
#ifdef _WIN64
    long minSpace = INT32_MAX;     //windows使用LLP64数字模型,long占4字节
#else
    long minSpace = INTMAX_MAX; //linux/unix使用LP64数据模型,long占8字节，
#endif
    for (int i = 0; i < thisHeight && i < rightHeight; i++) {
        long space = right->levelInfo(i)->_leftX
                - this->levelInfo(i)->_rightX;
        minSpace = min(minSpace, space);
    }
    return minSpace;
}

template<class T>
LevelInfo<T>* Nodebox<T>::levelInfo(int level) const{
    if (level < 0) return NULL;
    int levelY = _y + level;
    if (level >= treeHeight((Nodebox<T> *)this)) return NULL;
    
    vector<Nodebox<T> *> list;
    queue<Nodebox<T> *> queue;
    queue.push((Nodebox<T> *)this);

    // 层序遍历找出第level行的所有节点
    while (!queue.empty()) {
        Nodebox *box = queue.front();
        queue.pop();
        if (levelY == box->_y) {
            list.emplace_back(box);
        } else if (box->_y > levelY) break;

        if (box->_left) {
            queue.push(box->_left);
        }
        if (box->_right) {
            queue.push(box->_right);
        }
    }

    Nodebox *left = list.at(0);
    Nodebox *right = list.at(list.size() - 1);
    return new LevelInfo<T>(left, right);
}

template<class T>
ostream & operator<<(ostream &os, const Nodebox<T> *box){
    if (box) {
        //s == "┌" || s == "┐" || s == "│" || s == "─"
      /*  if (box->_desc == "┌") os << "┌";
        else if (box->_desc == "┐") os << "┐";
        else if (box->_desc == "│") os << "│";
        else if (box->_desc == "─") os << "─";
        else os << box->_node->_element;*/
        os << box->_desc;
    }
    return os;
}

#endif /* LevelOrderPrinter_hpp */

