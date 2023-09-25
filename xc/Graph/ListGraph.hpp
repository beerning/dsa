//
//  ListGraph.hpp
//  Graph
//
//  Created by berning on 2015/10/6.
//

#ifndef ListGraph_hpp
#define ListGraph_hpp

#include "Graph.hpp"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>

#include "hashCode.hpp"
#include "MiniHeap.hpp"
#include "UnionFind.hpp"

template<class V, class E>
class ListGraph : public Graph<V, E> {
    weightManager<E>* mgr;
    class Edge;
    int (*hash_func)(Edge *) = [](Edge *e)->int{ return e->from->hash() * 31 + e->to->hash();};
    bool (*equal_func)(Edge *, Edge *) = [](Edge *e1, Edge *e2)->bool{return e1->from->equalTo(e2->from) && e1->to->equalTo(e2->to);};
    
    typedef unordered_set<Edge *, decltype(hash_func), decltype(equal_func)>* HashSet;

    class Vertex {
        int (*hash_func)(Edge *) = [](Edge *e)->int{ return e->from->hash() * 31 + e->to->hash();};
        bool (*equal_func)(Edge *, Edge *) = [](Edge *e1, Edge *e2)->bool{return e1->from->equalTo(e2->from) && e1->to->equalTo(e2->to);};
    public:
        V value;
        Vertex(V _value) : value(_value) {}

        bool equalTo(Vertex *x) const{ return equals(x->value, value);}
        int hash() const{ return hashCode(value);}
        
        HashSet inEdges = new unordered_set<Edge *, decltype(hash_func), decltype(equal_func)>(0, hash_func, equal_func);
        HashSet outEdges = new unordered_set<Edge *, decltype(hash_func), decltype(equal_func)>(0, hash_func, equal_func);
    };
    int (*hash_vertex)(Vertex *) = [](Vertex *v)->int{ return v->hash();};
    bool (*equal_vertex)(Vertex *, Vertex *) = [](Vertex *v1, Vertex *v2)->bool{return v1->equalTo(v2);};
    
    class Edge {
    public:
        Vertex *from;
        Vertex *to;
        E weight;
        Edge(Vertex *_from, Vertex *_to) : from(_from), to(_to) {}
        
        EdgeInfo<V, E> *info() {
            return new EdgeInfo<V, E>(from->value, to->value, weight);
        }
    };

    function<int(Edge *, Edge *)> weightComparator = [this](Edge *e1, Edge *e2) -> int{//weightMgr msvc不能再Lambda中使用父类成员
        return this->mgr->compare(e1->weight, e2->weight);
    };
    unordered_map<V, Vertex *> *vertices = new unordered_map<V, Vertex *>;
    HashSet edges = new unordered_set<Edge *, decltype(hash_func), decltype(equal_func)>(0, hash_func, equal_func);
    
public:
    ListGraph() : ListGraph(NULL) {}
    ListGraph(weightManager<E> *weightMgr) : Graph<V, E>(weightMgr), mgr(weightMgr) {}
    
    void print(bool weight = false)const;
    
    int verticesSize() const override;
    int edgesSize() const override;
    
    void addVertex(V _v) override;
    void removeVertex(V _v) override;
    
    void addEdge(V _from, V _to, E _weight)override;
    void addEdge(V _from, V _to)override;
    void removeEdge(V _from, V _to)override;
    
private:
    void printEdge(string name, HashSet set, bool weight, bool CRLF = true) const;
    void dfs(Vertex *v, unordered_set<Vertex *> &visitedVertices, int &flag) const;
    
    unordered_set<EdgeInfo<V, E> *> *prim() const;
    unordered_set<EdgeInfo<V, E> *> *kruscal() const;
    
    typedef unordered_map<Vertex *, PathInfo<V, E> *, decltype(hash_vertex), decltype(equal_vertex)> Vertex_Map;
    typedef unordered_map<V, PathInfo<V, E> *> *V_Map;
    typedef unordered_map<V, V_Map> * VV_Map;
    
    V_Map dijkstra(V start) const;
    V_Map bellman_ford(V start) const;
    VV_Map floyd() const;
    
    PathInfo<V, E> *pathInfo(V from, V to, VV_Map msp) const;
    void relaxation(Edge *edge, PathInfo<V, E> *minPathInfo, Vertex_Map &map) const;
    bool relaxation(Edge *edge, PathInfo<V, E> *minPathInfo, V_Map map) const;
public:
    void bfs(V start) const override;
    void dfs(V start) const override;
    void dfs2(V start) const;
    
    vector<V> topologicalSort() const override;
    unordered_set<EdgeInfo<V, E> *> *mst() const override;
    V_Map shortestPath(V start) const override;
    VV_Map multiShortestPath() const override;
};

template<class V, class E>
int ListGraph<V, E>::verticesSize() const {
    return (int)vertices->size();
}

template<class V, class E>
int ListGraph<V, E>::edgesSize() const {
    return (int)edges->size();
}

template<class V, class E>
void ListGraph<V, E>::addVertex(V _v) {
    if (vertices->find(_v) != vertices->end()) return;
    vertices->emplace(_v, new Vertex(_v));
}

template<class V, class E>
void ListGraph<V, E>::removeVertex(V _v) {
    auto it = vertices->find(_v);
    if (it == vertices->end()) return;
    
    vertices->erase(it);
    Vertex *v = it->second;
    
    HashSet outs = v->outEdges;
    for (auto it = outs->begin(); it != outs->end(); ++it){
        Edge *edge = *it;
        edge->to->inEdges->erase(edge);
        edges->erase(edge);
        delete edge;
    }
    delete outs;
    
    HashSet ins = v->inEdges;
    for (auto it = ins->begin(); it != ins->end(); ++it){
        Edge *edge = *it;
        edge->from->outEdges->erase(edge);
        edges->erase(edge);
        delete edge;
    }
    delete ins;
    delete v;
}

template<class V, class E>
void ListGraph<V, E>::addEdge(V _from, V _to, E _weight) {
    Vertex *from = NULL;
    auto it = vertices->find(_from);
    if (it == vertices->end()) {
        from = new Vertex(_from);
        vertices->emplace(_from, from);
    }else{
        from = it->second;
    }
    
    Vertex *to = NULL;
    it = vertices->find(_to);
    if (it == vertices->end()) {
        to = new Vertex(_to);
        vertices->emplace(_to, to);
    }else{
        to = it->second;
    }
    
    Edge *edge = new Edge(from, to);
    edge->weight = _weight;
    if (from->outEdges->erase(edge)) {
        to->inEdges->erase(edge);
        edges->erase(edge);
    }

    from->outEdges->emplace(edge);
    to->inEdges->emplace(edge);
    edges->emplace(edge);
}

template<class V, class E>
void ListGraph<V, E>::addEdge(V _from, V _to) {
    addEdge(_from, _to, NULL);
}

template<class V, class E>
void ListGraph<V, E>::removeEdge(V _from, V _to) {
    auto it = vertices->find(_from);
    if (it == vertices->end()) return;
    Vertex *from = it->second;
    
    it = vertices->find(_to);
    if (it == vertices->end()) return;
    Vertex *to = it->second;
    
    Edge *edge = new Edge(from, to);
    
    if (from->outEdges->erase(edge)) {
        Edge *e = *edges->find(edge);
        to->inEdges->erase(edge);
        edges->erase(edge);
        delete e;
    }
    delete edge;
}

#pragma mark - print
template<class V, class E>
void ListGraph<V, E>::printEdge(string name, HashSet set,  bool weight, bool CRLF)const{
    cout << name << "[";
    int flag = 0;
    for (auto it = set->begin(); it != set->end(); ++it){
        if (flag > 0) cout << ", ";
        flag++;
        Edge *edge = *it;
        
        if (weight){
            E w = edge->weight ? edge->weight : 0;
            if (w)
                cout << edge->from->value << "-" << w << "->" << edge->to->value;
            else
                cout << edge->from->value << "-" << 0 << "->" << edge->to->value;
        }else{
            cout << edge->from->value << "->" << edge->to->value;
        }
    }
    cout << "]" << string(CRLF ? "\n" : ", ");
}

template<class V, class E>
void ListGraph<V, E>::print(bool weight)const{
    cout << "==============Vertex===================" << endl;
    for (auto it = vertices->begin(); it != vertices->end(); ++it){
        Vertex *v = it->second;
        cout << v->value << " : ";
        
        printEdge("outs", v->outEdges, weight, false);
        printEdge("ins", v->inEdges, weight);
    }
    cout << "==============Edge===================" << endl;
    printEdge("edges", edges, weight);
}

#pragma mark - traversal
template<class V, class E>
void ListGraph<V, E>::bfs(V start) const {
    auto it = vertices->find(start);
    if (it == vertices->end()) return;
    
    Vertex *v = it->second;
    queue<Vertex *> q;
    unordered_set<Vertex *> visitedVertices;
    int flag = 0;

    q.push(v);
    visitedVertices.emplace(v);
    
    while(!q.empty()) {
        v = q.front();
        q.pop();
        HashSet outs = v->outEdges;
    
        if (flag > 0) cout << ", ";
        cout << v->value;
        flag++;
        
        for (auto it = outs->begin(); it != outs->end(); ++it){
            Edge *edge = *it;
            if (visitedVertices.find(edge->to) != visitedVertices.end()) continue;
            q.push(edge->to);
            visitedVertices.emplace(edge->to);
        }
    }
    cout << endl;
}

template<class V, class E>
void ListGraph<V, E>::dfs(V start) const {
    auto it = vertices->find(start);
    if (it == vertices->end()) return;
    
    Vertex *v = it->second;
    int flag = 0;
    unordered_set<Vertex *> visitedVertices;
    dfs(v, visitedVertices, flag);
    cout << endl;
}

template<class V, class E>
void ListGraph<V, E>::dfs(Vertex *v, unordered_set<Vertex *> &visitedVertices, int &flag) const{
    visitedVertices.emplace(v);
    if (flag > 0) cout << ", ";
    cout << v->value;
    flag++;
    
    HashSet outs = v->outEdges;
    for (auto it = outs->begin(); it != outs->end(); ++it) {
        Edge *edge = *it;
        if (visitedVertices.find(edge->to) != visitedVertices.end()) continue;
        dfs(edge->to, visitedVertices, flag);
    }
}

template<class V, class E>
void ListGraph<V, E>::dfs2(V start) const {
    auto it = vertices->find(start);
    if (it == vertices->end()) return;
    
    Vertex *v = it->second;
    stack<Vertex *> stack;
    unordered_set<Vertex *> visitedVertices;
    cout << v->value;
    stack.emplace(v);
    visitedVertices.emplace(v);
    
    while (!stack.empty()) {
        Vertex *v = stack.top();
        stack.pop();
        HashSet outs = v->outEdges;
        for (auto it = outs->begin(); it != outs->end(); ++it) {
            Edge *edge = *it;
            if (visitedVertices.find(edge->to) != visitedVertices.end()) continue;
            stack.emplace(edge->from);
            stack.emplace(edge->to);
            visitedVertices.emplace(edge->to);
            cout << ", ";
            cout << edge->to->value;
            break;
        }
    }
    cout << endl;
}

#pragma mark - Topological Sort
template<class V, class E>
vector<V> ListGraph<V, E>::topologicalSort() const {
    //statistics
    vector<V> list;
    queue<Vertex *> q;
    unordered_map<Vertex *, int, decltype(hash_vertex), decltype(equal_vertex)> table(5, hash_vertex, equal_vertex);
    
    auto it = vertices->begin();
    while (it != vertices->end()) {
        Vertex *v = it->second;
        size_t inc = v->inEdges->size();
        if (inc == 0) q.push(v);
        else table.emplace(v, inc);
        ++it;
    }
    
    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        list.emplace_back(v->value);
        HashSet outs = v->outEdges;
        for (auto it = outs->begin(); it != outs->end(); ++it) {
            Vertex *to = (*it)->to;
            int inc = table[to] - 1;
            if (inc == 0) q.push(to);
            else table[to] = inc;
        }
    }
    return list;
}

#pragma mark - Minimum Spanning Tree
template<class V, class E>
unordered_set<EdgeInfo<V, E> *> *ListGraph<V, E>::mst() const{
    srand((unsigned)time(nullptr));
    return rand() % 101 / 100.0 > 0.5 ? prim() : kruscal();
}

template<class V, class E>
unordered_set<EdgeInfo<V, E> *> *ListGraph<V, E>::prim() const{
    cout << __func__ << ": " << endl;
    auto it = vertices->begin();
    if (it == vertices->end()) return nullptr;
    Vertex *begin = it->second;
    unordered_set<EdgeInfo<V, E> *> *mst = new unordered_set<EdgeInfo<V, E> *>; //生成树的边集
    unordered_set<Vertex *> cutSet; //横切边的出发点集
    cutSet.emplace(begin);
    
    //批量建堆
    HashSet outs = begin->outEdges;
    unordered_set<Edge *> set;
    for (auto it = outs->begin(); it != outs->end(); ++it)
        set.emplace(*it);
    MiniHeap<Edge *> heap(&set, weightComparator);
    
    size_t size = vertices->size();
    while (!heap.isEmpty() && cutSet.size() < size) {
        Edge *edge = heap.remove();
        if (cutSet.find(edge->to) != cutSet.end()) continue;
        mst->emplace(edge->info());
        cutSet.emplace(edge->to);
        
        outs = edge->to->outEdges;
        unordered_set<Edge *> set;
        for (auto it = outs->begin(); it != outs->end(); ++it)
            set.emplace(*it);
        heap.add(&set);
    }
    return mst;
}

template<class V, class E>
unordered_set<EdgeInfo<V, E> *> *ListGraph<V, E>::kruscal() const{
    cout << __func__ << ": " << endl;
    size_t edgeSize = vertices->size() - 1;
    if (edgeSize < 0) return nullptr;
    unordered_set<EdgeInfo<V, E> *> *mst = new unordered_set<EdgeInfo<V, E> *>;
    
    //初始化并查集
    UnionFind<Vertex *> uf;
    for (auto it = vertices->begin(); it != vertices->end(); ++it)
        uf.set(it->second);
    
    //批量建堆
    unordered_set<Edge *> set;
    for (auto it = edges->begin(); it != edges->end(); ++it)
        set.emplace(*it);
    MiniHeap<Edge *> heap(&set, weightComparator);
    
    while (!heap.isEmpty() && mst->size() < edgeSize) {
        Edge *edge = heap.remove();
        if (uf.isSame(edge->from, edge->to)) continue;
        mst->emplace(edge->info());
        uf.merge(edge->from, edge->to);
    }
    return mst;
}

#pragma mark - Shortest Path
template<class V, class E>
unordered_map<V, PathInfo<V, E> *> *ListGraph<V, E>::shortestPath(V start) const{
    //return dijkstra(start);
    return bellman_ford(start);
}

template<class V, class E>
unordered_map<V, PathInfo<V, E> *> *ListGraph<V, E>::dijkstra(V start)const {
    cout << __func__ << ": " << endl;
    auto it = vertices->find(start);
    if (it == vertices->end()) return nullptr;
    
    Vertex *begin = it->second;
    V_Map sp = new unordered_map<V, PathInfo<V, E> *>;
    Vertex_Map table(5, hash_vertex, equal_vertex);
    
    HashSet outs = begin->outEdges;
    for (auto it = outs->begin(); it != outs->end(); ++it) {
        Edge *edge = *it;
        PathInfo<V, E> *pathInfo = new PathInfo<V, E>(edge->weight);
        pathInfo->edgesInfo.emplace_back(edge->info());
        table.emplace(edge->to, pathInfo);
    }
    
    while (!table.empty()) {
        //get the minimum weight
        auto min = table.begin();
        for (auto it = table.begin(); it != table.end(); ++it){
            if (this->weightMgr->compare(min->second->weight, it->second->weight) <= 0) continue;
            min = it;
        }
        //first minPath
        Vertex *minVertex = min->first;
        PathInfo<V, E> *minPathInfo = min->second;
        sp->emplace(minVertex->value, minPathInfo);
        table.erase(min);
        
        //relaxation
        HashSet outs = minVertex->outEdges;
        for (auto iterator = outs->begin(); iterator != outs->end(); ++iterator){
            Edge *edge = *iterator;
            if (sp->find(edge->to->value) != sp->end()) continue;
            relaxation(edge, minPathInfo, table);
        }
    }
    return sp;
}

template<class V, class E>
unordered_map<V, PathInfo<V, E> *> *ListGraph<V, E>::bellman_ford(V start) const {
    cout << __func__ << ": " << endl;
    auto it = vertices->find(start);
    if (it == vertices->end()) return nullptr;
    V v = it->first;
    
    V_Map sp = new unordered_map<V, PathInfo<V, E> *>;
    PathInfo<V, E> *pathInfo = new PathInfo<V, E>(this->weightMgr->zero());
    sp->emplace(v, pathInfo);
    
    size_t count = vertices->size() - 1;
    for (int i = 0; i < count; ++i) {
        for (auto iterator = edges->begin(); iterator != edges->end(); ++iterator) {
            Edge *edge = *iterator;
            auto from_it = sp->find(edge->from->value);
            if (from_it == sp->end()) continue;
            relaxation(edge, from_it->second, sp);
        }
    }
    
    for (int i = 0; i < count; ++i) {
        for (auto iterator = edges->begin(); iterator != edges->end(); ++iterator) {
            Edge *edge = *iterator;
            auto from_it = sp->find(edge->from->value);
            if (from_it == sp->end()) continue;
            if (relaxation(edge, from_it->second, sp)){
                cout << "有负权环" << endl;
                return nullptr;
            }
        }
    }
    sp->erase(v);
    return sp;
}

template<class V, class E>
unordered_map<V, unordered_map<V, PathInfo<V, E> *> *> *ListGraph<V, E>::multiShortestPath() const {
    return floyd();
}

template<class V, class E>
unordered_map<V, unordered_map<V, PathInfo<V, E> *> *> *ListGraph<V, E>::floyd() const {
    VV_Map msp = new unordered_map<V, V_Map>;
    for (auto it = edges->begin(); it != edges->end(); ++it) {
        Edge *edge = *it;
        auto mit = msp->find(edge->from->value);
        V_Map sp = nullptr;
        if (mit == msp->end()) {
            sp = new unordered_map<V, PathInfo<V, E> *>;
            msp->emplace(edge->from->value, sp);
        }else {
            sp = mit->second;
        }
        PathInfo<V, E> *pathInfo = new PathInfo<V, E>(edge->weight);
        pathInfo->edgesInfo.emplace_back(edge->info());
        sp->emplace(edge->to->value, pathInfo);
    }
    
    for_each(vertices->begin(), vertices->end(), [&](typename unordered_map<V, Vertex *>::reference p2){
        for_each(vertices->begin(), vertices->end(), [&](typename unordered_map<V, Vertex *>::reference p1){
            for_each(vertices->begin(), vertices->end(), [&](typename unordered_map<V, Vertex *>::reference p3){

                if (p1.second->equalTo(p2.second) || p2.second->equalTo(p3.second) || p1.second->equalTo(p3.second)) return;

                PathInfo<V, E> *path12 = pathInfo(p1.first, p2.first, msp);
                if (path12 == nullptr) return;
                PathInfo<V, E> *path23 = pathInfo(p2.first, p3.first, msp);
                if (path23 == nullptr) return;

                PathInfo<V, E> *path13 = pathInfo(p1.first, p3.first, msp);

                E newer = this->weightMgr->add(path12->weight, path23->weight);
                if (path13 != nullptr && this->weightMgr->compare(path13->weight, newer) <= 0) return;

                if (path13 == nullptr) {
                    path13 = new PathInfo<V, E>;
                    msp->at(p1.first)->emplace(p3.first, path13);
                }else {
                    path13->edgesInfo.clear();
                }
                path13->weight = newer;
                for (auto it = path12->edgesInfo.begin(); it != path12->edgesInfo.end(); ++it)
                    path13->edgesInfo.emplace_back(*it);
                for (auto it = path23->edgesInfo.begin(); it != path23->edgesInfo.end(); ++it)
                    path13->edgesInfo.emplace_back(*it);
            });
        });
    });
    return msp;
}
template<class V, class E>
PathInfo<V, E> *ListGraph<V, E>::pathInfo(V from, V to, VV_Map msp) const {
    auto mit = msp->find(from);
    if (mit == msp->end()) return nullptr;
    V_Map sp = mit->second;
    auto it = sp->find(to);
    if (it == sp->end()) return nullptr;
    return it->second;
}

#pragma mark - relaxation
template<class V, class E>
void ListGraph<V, E>::relaxation(Edge *edge, PathInfo<V, E> *minPathInfo, Vertex_Map &table) const {
    E newer = this->weightMgr->add(minPathInfo->weight, edge->weight);
    auto it = table.find(edge->to);
    if (it != table.end() && this->weightMgr->compare(it->second->weight, newer) <= 0) return;
    
    PathInfo<V, E> *pathInfo = nullptr;
    if (it == table.end()) {
        pathInfo = new PathInfo<V, E>;
        table.emplace(edge->to, pathInfo);
    }else {
        pathInfo = it->second;
        pathInfo->edgesInfo.clear();
    }
    
    pathInfo->weight = newer;
    for (auto it = minPathInfo->edgesInfo.begin(); it != minPathInfo->edgesInfo.end(); ++it) {
        pathInfo->edgesInfo.emplace_back(*it);
    }
    pathInfo->edgesInfo.emplace_back(edge->info());
}

template<class V, class E>
bool ListGraph<V, E>::relaxation(Edge *edge, PathInfo<V, E> *fromPathInfo, V_Map sp) const{
    E newer = this->weightMgr->add(fromPathInfo->weight, edge->weight);
    auto to_it = sp->find(edge->to->value);
    if (to_it != sp->end() && this->weightMgr->compare(to_it->second->weight, newer) <= 0) return false;
    
    PathInfo<V, E> *pathInfo = nullptr;
    if (to_it == sp->end()) {
        pathInfo = new PathInfo<V, E>;
        sp->emplace(edge->to->value, pathInfo);
    }else {
        pathInfo = to_it->second;
        pathInfo->edgesInfo.clear();
    }
    
    pathInfo->weight = newer;
    for (auto it = fromPathInfo->edgesInfo.begin(); it != fromPathInfo->edgesInfo.end(); ++it)
        pathInfo->edgesInfo.emplace_back(*it);
    pathInfo->edgesInfo.emplace_back(edge->info());

    return true;
}


//template<class V, class E>
//unordered_map<V, unordered_map<V, PathInfo<V, E> *> *> *ListGraph<V, E>::floyd() const {
//    VV_Map msp = new unordered_map<V, unordered_map<V, PathInfo<V, E> *> *>;
//    for (auto it = edges->begin(); it != edges->end(); ++it) {
//        Edge *edge = *it;
//        auto mit = msp->find(edge->from->value);
//        V_Map sp = nullptr;
//        if (mit == msp->end()) {
//            sp = new unordered_map<V, PathInfo<V, E> *>;
//            msp->emplace(edge->from->value, sp);
//        }else {
//            sp = mit->second;
//        }
//        PathInfo<V, E> *pathInfo = new PathInfo<V, E>(edge->weight);
//        pathInfo->edgesInfo.emplace_back(edge->info());
//        sp->emplace(edge->to->value, pathInfo);
//    }
//    for (auto p2 = vertices->begin(); p2 != vertices->end(); ++p2) {
//        for (auto p1 = vertices->begin(); p1 != vertices->end(); ++p1) {
//            for (auto p3 = vertices->begin(); p3 != vertices->end(); ++p3) {
//                if (p1->second->equalTo(p2->second)) break;
//                if(p2->second->equalTo(p3->second) || p1->second->equalTo(p3->second)) continue;
//
//                PathInfo<V, E> *path12 = pathInfo(p1->first, p2->first, msp);
//                if (path12 == nullptr) break;;
//                PathInfo<V, E> *path23 = pathInfo(p2->first, p3->first, msp);
//                if (path23 == nullptr) continue;
//
//                PathInfo<V, E> *path13 = pathInfo(p1->first, p3->first, msp);
//
//                E newer = this->weightMgr->add(path12->weight, path23->weight);
//                if (path13 != nullptr && this->weightMgr->compare(path13->weight, newer) <= 0) continue;
//
//                if (path13 == nullptr) {
//                    path13 = new PathInfo<V, E>;
//                    msp->at(p1->first)->emplace(p3->first, path13);
//                }else {
//                    path13->edgesInfo.clear();
//                }
//                path13->weight = newer;
//                for (auto it = path12->edgesInfo.begin(); it != path12->edgesInfo.end(); ++it)
//                    path13->edgesInfo.emplace_back(*it);
//                for (auto it = path23->edgesInfo.begin(); it != path23->edgesInfo.end(); ++it)
//                    path13->edgesInfo.emplace_back(*it);
//            }
//        }
//    }
//    return msp;
//}

#endif /* ListGraph_hpp */
