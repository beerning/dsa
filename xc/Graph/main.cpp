//
//  main.cpp
//  Graph
//
//  Created by berning on 2015/10/1.
//

#include <iostream>
using namespace std;
#include "ListGraph.hpp"

#include "testHashSet.h"

void Graph0(){
    ListGraph<string, int> graph;
    graph.addEdge("lisa", "boning", 26);
    graph.addEdge("boning", "yudan");
    graph.addEdge("boning", "huahua", 27);
    graph.addEdge("boning", "yaya");
    graph.addEdge("boning", "qiqiao", 20);
    graph.addEdge("qiqiao", "ning", 18);

    graph.print(1);
    
    graph.bfs("lisa");
    graph.dfs("lisa");
    graph.dfs2("lisa");
}

void Graph1(){
    ListGraph<string, string *> graph;
    
    graph.addEdge("1", "2");
    
    graph.addEdge("1", "3");
    graph.addEdge("1", "5");

    graph.addEdge("2", "0");
    
    graph.addEdge("3", "5");
    
    graph.addEdge("5", "6");
    graph.addEdge("5", "7");

    graph.addEdge("6", "2");
    
    graph.addEdge("7", "6");

    cout << "edgesSize = "<< graph.edgesSize() << endl;
    cout << "verticesSize = " << graph.verticesSize() << endl;
    graph.print();
    
//    cout << "remove: " << endl;
//    graph.removeEdge("v0", "v2");
//    graph.removeEdge("v2", "v0");
////
//    graph.removeVertex("v0");
//    graph.print();
    
    cout << "bfs: " << endl;
    graph.bfs("1");
    
    cout << "dfs: " << endl;
    graph.dfs("1");
}

void Graph2(){
    ListGraph<string, string *> graph;
    
    graph.addEdge("A", "B");
    graph.addEdge("B", "A");

    graph.addEdge("A", "F");
    graph.addEdge("F", "A");

    graph.addEdge("B", "C");
    graph.addEdge("C", "B");

    graph.addEdge("B", "I");
    graph.addEdge("I", "B");

    graph.addEdge("B", "G");
    graph.addEdge("G", "B");

    graph.addEdge("C", "I");
    graph.addEdge("I", "C");

    graph.addEdge("C", "D");
    graph.addEdge("D", "C");

    graph.addEdge("D", "E");
    graph.addEdge("E", "D");

    graph.addEdge("D", "G");
    graph.addEdge("G", "D");

    graph.addEdge("D", "H");
    graph.addEdge("H", "D");

    graph.addEdge("D", "I");
    graph.addEdge("I", "D");

    graph.addEdge("E", "F");
    graph.addEdge("F", "E");

    graph.addEdge("E", "H");
    graph.addEdge("H", "E");

    graph.addEdge("F", "G");
    graph.addEdge("G", "F");

    graph.addEdge("G", "H");
    graph.addEdge("H", "G");

    cout << "edgesSize = "<< graph.edgesSize() << endl;
    cout << "verticesSize = " << graph.verticesSize() << endl;
    graph.print();
    
    cout << "bfs: " << endl;
    graph.bfs("A");
}

void Graph3(){
    ListGraph<string, string *> graph;
    
    graph.addEdge("0", "1");
    graph.addEdge("1", "0");
    
    graph.addEdge("1", "2");
    graph.addEdge("2", "1");
    
    graph.addEdge("1", "3");
    graph.addEdge("3", "1");

    graph.addEdge("1", "5");
    graph.addEdge("5", "1");

    graph.addEdge("1", "6");
    graph.addEdge("6", "1");

    graph.addEdge("2", "4");
    graph.addEdge("4", "2");

    graph.addEdge("3", "7");
    graph.addEdge("7", "3");

    cout << "edgesSize = "<< graph.edgesSize() << endl;
    cout << "verticesSize = " << graph.verticesSize() << endl;
    graph.print();

    cout << "bfs: " << endl;
    graph.bfs("1");
    
    cout << "dfs: " << endl;
    graph.dfs("1");
    
    cout << "dfs2: " << endl;
    graph.dfs2("1");

}

void Graph4(){
    ListGraph<string, string *> graph;
    
    graph.addEdge("A", "B");
    graph.addEdge("A", "D");

    graph.addEdge("B", "F");
    graph.addEdge("C", "B");
    graph.addEdge("C", "F");

    graph.addEdge("E", "A");
    graph.addEdge("E", "B");
    graph.addEdge("E", "F");

    cout << "edgesSize = "<< graph.edgesSize() << endl;
    cout << "verticesSize = " << graph.verticesSize() << endl;
    graph.print();
    
    cout << "==============bfs===================" << endl;
    graph.bfs("C");
    
    cout << "==============dfs===================" << endl;
    graph.dfs("C");
    
    cout << "==============dfs2===================" << endl;
    graph.dfs2("C");
    
    cout << "==============topologicalSort===================" << endl;
    vector<string> list = graph.topologicalSort();
    
    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";
    cout << endl;
    
    cout << "==============mst===================" << endl;
        
    graph.mst();
    
    cout << endl;

}

template<>
class weightManager<int>{
public:
    int compare(int w1, int w2) const {
        return w1 > w2 ? 1 : w1 < w2 ? -1 : 0;
    };
    int add(int w1, int w2) const { return w1 + w2;};
    int zero() const{return 0;}
};

void Graph_mst(){
    
    ListGraph<string, int> graph(new weightManager<int>);
    
    graph.addEdge("A", "B", 4);
    graph.addEdge("B", "A", 4);

    graph.addEdge("A", "H", 8);
    graph.addEdge("H", "A", 8);


    graph.addEdge("B", "C", 8);
    graph.addEdge("C", "B", 8);

    graph.addEdge("B", "H", 11);
    graph.addEdge("H", "B", 11);

    graph.addEdge("C", "D", 7);
    graph.addEdge("D", "C", 7);

    graph.addEdge("C", "F", 4);
    graph.addEdge("F", "C", 4);

    graph.addEdge("C", "I", 2);
    graph.addEdge("I", "C", 2);

    graph.addEdge("D", "E", 9);
    graph.addEdge("E", "D", 9);

    graph.addEdge("D", "F", 14);
    graph.addEdge("F", "D", 14);

    graph.addEdge("E", "F", 10);
    graph.addEdge("F", "E", 10);

    graph.addEdge("F", "G", 2);
    graph.addEdge("G", "F", 2);

    graph.addEdge("G", "I", 6);
    graph.addEdge("I", "G", 6);

    graph.addEdge("G", "H", 1);
    graph.addEdge("H", "G", 1);

    graph.addEdge("H", "I", 7);
    graph.addEdge("I", "H", 7);

    cout << "edgesSize = "<< graph.edgesSize() << endl;
    cout << "verticesSize = " << graph.verticesSize() << endl;
    graph.print(true);
    
    cout << "==============bfs===================" << endl;
    graph.bfs("C");
    
    cout << "==============dfs===================" << endl;
    graph.dfs("C");
    
    cout << "==============dfs2===================" << endl;
    graph.dfs2("C");
        
    cout << "==============mst===================" << endl;
        
    unordered_set<EdgeInfo<string, int> *> *sets = graph.mst();
    for (auto it = sets->begin(); it != sets->end(); ++it)
        cout << *it << " ";
    cout << endl;

}

void Graph_sp(){
    
    ListGraph<string, int> graph(new weightManager<int>);
    //{//dijkstra
    //    graph.addEdge("A", "B", 10);
    //    graph.addEdge("A", "D", 30);
    //    graph.addEdge("A", "E", 100);

    //    graph.addEdge("B", "C", 50);
    //    graph.addEdge("C", "E", 10);

    //    graph.addEdge("D", "C", 20);
    //    graph.addEdge("D", "E", 60);
    //}
    
    
    {//bell_man
        graph.addEdge("A", "B", 10);
        graph.addEdge("A", "E", 8);
        graph.addEdge("B", "C", 8);
        graph.addEdge("B", "E", -5);
        graph.addEdge("D", "C", 2);
        graph.addEdge("D", "F", 6);
        graph.addEdge("E", "D", 7);
        graph.addEdge("E", "F", 3);
    }
    
    //负权环
//    {//bell_man
//        graph.addEdge("A", "B", 4);
//        graph.addEdge("A", "E", 8);
//        graph.addEdge("B", "C", 8);
//        graph.addEdge("B", "E", 11);
//        graph.addEdge("D", "C", 2);
//        graph.addEdge("D", "F", 6);
//        graph.addEdge("E", "D", 7);
//        graph.addEdge("F", "E", -20);
//    }
    cout << "edgesSize = "<< graph.edgesSize() << endl;
    cout << "verticesSize = " << graph.verticesSize() << endl;
    graph.print(true);
    
    cout << "==============bfs===================" << endl;
    graph.bfs("C");
    
    cout << "==============dfs===================" << endl;
    graph.dfs("C");
    
    cout << "==============dfs2===================" << endl;
    graph.dfs2("C");
        
    cout << "==============sp===================" << endl;
        
    unordered_map<string, PathInfo<string, int> *> *map = graph.shortestPath("A");
    if (map == nullptr) return;
    for (auto it = map->begin(); it != map->end(); ++it)
        cout << it->first << " : " << it->second << endl;
    
    cout << "==============msp===================" << endl;
    typedef unordered_map<string, unordered_map<string, PathInfo<string, int> *> *> * VV_Map;
    typedef unordered_map<string, PathInfo<string, int> *> *V_Map;

    VV_Map mmap = graph.multiShortestPath();
    for (auto mit = mmap->begin(); mit != mmap->end(); ++mit) {
        cout << "start("<< mit->first << ")" << endl;
        V_Map map = mit->second;
        for (auto it = map->begin(); it != map->end(); ++it){
            cout << it->first << " : " << it->second << endl;
        }
    }
}


void testGraph(){
    //Graph0();
//    Graph1();
//    Graph2();
//    Graph3();
//    Graph4();
    //Graph_mst();
    Graph_sp();
}

int main(int argc, const char * argv[]) {
    testGraph();
//    testHashSet();
//    testHashMap();
//    testMiniHeap();
    
    return 0;
}


//月薪 50000
// 公积金 36675 * 12% =
