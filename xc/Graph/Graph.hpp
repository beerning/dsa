//
//  Graph.hpp
//  Graph
//
//  Created by berning on 2015/10/6.
//

#ifndef Graph_hpp
#define Graph_hpp
#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>

template<class V, class E> class EdgeInfo;
template<class V, class E> ostream & operator<<(ostream &os, const EdgeInfo<V, E> *edgeInfo);

template<class V, class E>
class EdgeInfo{
public:
    V from;
    V to;
    E weight;
    EdgeInfo(V _from, V _to, E _weight) : from(_from), to(_to), weight(_weight) {}
    
    friend ostream & operator<< <>(ostream &os, const EdgeInfo<V, E> *edgeInfo);
};

template<class V, class E>
ostream & operator<<(ostream &os, const EdgeInfo<V, E> *edgeInfo) {
    return os << edgeInfo->from << "-" << edgeInfo->weight << "-" << edgeInfo->to;
}

template<class V, class E> class PathInfo;
template<class V, class E> ostream & operator<<(ostream &os, const PathInfo<V, E> *pathInfo);

template<class V, class E>
class PathInfo{
public:
    E weight;
    list<EdgeInfo<V, E> *> edgesInfo;
    PathInfo() {}
    PathInfo(E _weight) : weight(_weight) {}
    friend ostream & operator<< <>(ostream &os, const PathInfo<V, E> *pathInfo);
};

template<class V, class E>
ostream & operator<<(ostream &os, const PathInfo<V, E> *pathInfo){
    list<EdgeInfo<V, E> *> edgesInfo = pathInfo->edgesInfo;
    auto it = edgesInfo.begin();
    EdgeInfo<V, E>* edgeInfo = nullptr;
    while (it != edgesInfo.end()) {
        edgeInfo = *it;
        if (it == edgesInfo.begin()) os << edgeInfo->from;
        os << "-" << edgeInfo->weight << "->" << edgeInfo->to;
        ++it;
    }
    os << " : " << pathInfo->weight;
    return os;
}

template<class E>
class weightManager{
public:
    int compare(E w1, E w2) const {return 0;}
    E add(E w1, E w2) const { return w1;}
    E zero() const {
        E weight = nullptr;
        return weight;
    }
};

template<class V, class E>
class Graph{
protected:
    weightManager<E> *weightMgr;
    virtual int verticesSize() const = 0;
    virtual int edgesSize() const = 0;
    
    virtual void addVertex(V _v) = 0;
    virtual void removeVertex(V _v) = 0;
    
    virtual void addEdge(V _from, V _to, E _weight) = 0;
    virtual void addEdge(V from, V to) = 0;
    virtual void removeEdge(V _from, V _to) = 0;
    
    virtual void bfs(V start) const = 0;
    virtual void dfs(V start) const = 0;
    
    virtual vector<V> topologicalSort() const = 0;

    virtual unordered_set<EdgeInfo<V, E> *> *mst() const = 0;
    virtual unordered_map<V, PathInfo<V, E> *> *shortestPath(V start) const = 0;
    virtual unordered_map<V, unordered_map<V, PathInfo<V, E> *> *> *multiShortestPath() const = 0;

public:
    Graph() : Graph(NULL) {}
    Graph(weightManager<E>* _weightMgr) : weightMgr(_weightMgr) {}
};

#endif /* Graph_hpp */
