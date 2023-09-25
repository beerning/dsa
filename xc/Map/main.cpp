//
//  main.cpp
//  Map
//
//  Created by ; on 2015/5/23.
//

#include <iostream>
using namespace std;
#include <string>
#include "map/TreeMap.hpp"
#include "map/HashMap.hpp"
#include "map/LinkedHashMap.hpp"
#include "Tools.h"

void testTreeMap(){

    TreeMap *map = new TreeMap;
    map->put(String::valueOf("name"), String::valueOf("Jack"));
    map->put(Integer::valueOf(23),  Integer::valueOf(20));
    map->put(Long::valueOf(200.0), String::valueOf("Rose"));
    map->put(Short::valueOf(20), String::valueOf("Rose"));
    map->put(Float::valueOf(20.f), String::valueOf("Jones"));
    map->put(Double::valueOf(33.0), String::valueOf("Rose"));
    map->put(Double::valueOf(30.0), String::valueOf("Rose"));

    map->traversal();
}

void test1(HashMap *map){
    
    map->put(Long::valueOf(-20), String::valueOf("Adam"));
    map->put(Integer::valueOf(10), String::valueOf("Bob"));
    map->put(String::valueOf("Jack"), String::valueOf("Cucci"));

    map->put(String::valueOf("name"), String::valueOf("Danny"));
    map->put(Integer::valueOf(23),  Integer::valueOf(20));
    map->put(Long::valueOf(200.0), String::valueOf("Eilin"));
    map->put(Short::valueOf(36), String::valueOf("Fib"));
    map->put(Float::valueOf(20.f), String::valueOf("Jones"));
    map->put(Double::valueOf(33.0), String::valueOf("Klay"));
    map->put(Double::valueOf(30.0), String::valueOf("Rose"));
    map->put(NULL, String::valueOf("Zion"));

    cout << "size = " << map->size() << endl;
    map->traversal();

    cout << "-------------------------------" << endl;;

    for (int i = 0; i < 48; i++){
        string *s = new string("Curry");
        s->append(to_string(i));
        const char *cs = s->data();
        map->put(Integer::valueOf(i), String::valueOf(cs));
    }
    
    cout << "size = " << map->size() << endl;
    cout << "isEmpty = " << map->isEmpty() << endl;
    map->traversal();
    
    
    cout << "-------------------------------" << endl;;
    
    
//    Long *k = Long::valueOf(-20); //v
//    Integer *k = Integer::valueOf(10);    //v
//    String *k = String::valueOf("Jack"); //v
//    String *k = String::valueOf("name"); //v
//    Integer *k = Integer::valueOf(23); //v
//    Long *k = Long::valueOf(200.0); //v
//    Short *k = Short::valueOf(36);  //v
//    Integer *k = Integer::valueOf(36);  //v

//    Float *k = Float::valueOf(20.f);  ///v
    Double *k = Double::valueOf(33.0);  //v

    id v = map->get(k);
    if (v) cout << v->toString() << endl;
    else cout << "key is not exists." << endl;;
    
    cout << "-------------------------------" << endl;;

    cout << "containsKey = " << map->containsKey(Short::valueOf(36)) << endl;
    cout << "containsValue = " << map->containsValue(String::valueOf("Curry39")) << endl;

    cout << "-------------------------------" << endl;;
    map->remove(Long::valueOf(-20));
    map->remove(Double::valueOf(33.0));
    map->remove(Float::valueOf(20.f));
    for (int i = 0; i < 48; i++){
        map->remove(Integer::valueOf(i));
    }
    cout << "size = " << map->size() << endl;
    map->traversal();

    cout << "-------------------------------" << endl;;
    map->clear();
    cout << "size = " << map->size() << endl;
    map->traversal();
}

void test2(HashMap *map) {
    for (int i = 1; i <= 20; i++) {
        map->put(Integer::valueOf(i), Integer::valueOf(i));
    }
    for (int i = 5; i <= 7; i++) {
        map->put(Integer::valueOf(i), Integer::valueOf(i + 5));
    }
    
    Asserts::test(map->size() == 19);
    Asserts::test(map->get(Integer::valueOf(4))->toString() ==  Integer::valueOf(4)->toString());
    Asserts::test(map->get(Integer::valueOf(5))->toString() == Integer::valueOf(10)->toString());
    Asserts::test(map->get(Integer::valueOf(6))->toString() == Integer::valueOf(11)->toString());
    Asserts::test(map->get(Integer::valueOf(7))->toString() == Integer::valueOf(12)->toString());
    Asserts::test(map->get(Integer::valueOf(8))->toString() == Integer::valueOf(8)->toString());
    
    map->traversal();

}

void test3(HashMap *map) {
    map->put(NULL, Integer::valueOf(1)); // 1
    map->put(new Object(), Integer::valueOf(2)); // 2
    map->put(String::valueOf("jack"), Integer::valueOf(3)); // 3
    map->put(Integer::valueOf(10), Integer::valueOf(4)); // 4
    map->put(new Object(), Integer::valueOf(5)); // 5
    map->put(String::valueOf("jack"), Integer::valueOf(6));
    map->put(Integer::valueOf(10), Integer::valueOf(7));
    map->put(NULL, Integer::valueOf(8));
    map->put(Integer::valueOf(10), NULL);
    Asserts::test(map->size() == 5);
    Asserts::test(map->get(NULL)->toString() == Integer::valueOf(8)->toString());
    Asserts::test(map->get(String::valueOf("jack"))->toString() == Integer::valueOf(6)->toString());
    Asserts::test(map->get(Integer::valueOf(10)) == NULL);
    Asserts::test(map->get(new Object()) == NULL);
    Asserts::test(map->containsKey(Integer::valueOf(10)));
    Asserts::test(map->containsKey(NULL));
    Asserts::test(map->containsValue(NULL));
    Asserts::test(map->containsValue(Integer::valueOf(1)) == false);
    
    map->traversal();
}

void test4(HashMap *map) {
    map->put(String::valueOf("jack"), Integer::valueOf(1));
    map->put(String::valueOf("rose"), Integer::valueOf(2));
    map->put(String::valueOf("jim"), Integer::valueOf(3));
    map->put(String::valueOf("jake"), Integer::valueOf(4));

    map->remove(String::valueOf("jack"));
    map->remove(String::valueOf("jim"));
    for (int i = 1; i <= 10; i++) {
        string *s = new string("test");
        s->append(to_string(i));
        const char *cs = s->data();
        map->put(String::valueOf(cs), Integer::valueOf(i));

        map->put(Integer::valueOf(i), Integer::valueOf(i));
    }

    for (int i = 1; i <= 7; i++) {
        map->put(Integer::valueOf(i), Integer::valueOf(i + 5));
    } 

    for (int i = 5; i <= 7; i++) {
        Asserts::test(map->remove(Integer::valueOf(i))->toString() == Integer::valueOf(i + 5)->toString());
    }

    Asserts::test(map->size() == 19);
    Asserts::test(map->get(Integer::valueOf(1))->toString() == Integer::valueOf(6)->toString());
    Asserts::test(map->get(Integer::valueOf(2))->toString() == Integer::valueOf(7)->toString());
    Asserts::test(map->get(Integer::valueOf(3))->toString() == Integer::valueOf(8)->toString());
    Asserts::test(map->get(Integer::valueOf(4))->toString() == Integer::valueOf(9)->toString());
    Asserts::test(map->get(Integer::valueOf(5)) == NULL);
    Asserts::test(map->get(Integer::valueOf(6)) == NULL);
    Asserts::test(map->get(Integer::valueOf(7)) == NULL);
    Asserts::test(map->get(Integer::valueOf(8))->toString() == Integer::valueOf(8)->toString());

    map->traversal();
}

#include <unordered_map>

class Person{};

void testHashSet();
int main(int argc, const char * argv[]) {

    //testTreeMap();
    //test1(new HashMap());
    //test2(new HashMap());
    //test3(new HashMap());
    //test4(new HashMap());
    
    test1(new LinkedHashMap());
//    test2(new LinkedHashMap());
//    test3(new LinkedHashMap());
//    test4(new LinkedHashMap());
    
//    testHashSet();
    
    //unordered_map<Person, int> map;
        
    return 0;
}


#include "HashSet.hpp"
void testHashSet(){
    HashSet set;
    set.add(String::valueOf("Adam"));
    set.add(Integer::valueOf(10));
    set.add(String::valueOf("Jack"));

    set.add(String::valueOf("Danny"));
    set.add(Integer::valueOf(23));
    set.add(String::valueOf("Eilin"));
    set.add(String::valueOf("Fib"));
    set.add(String::valueOf("Jones"));
    set.add(String::valueOf("Klay"));
    set.add(String::valueOf("Rose"));
    set.add(NULL);
    
    set.traversal();
    
    cout << set.contains(Integer::valueOf(23)) << endl;
    set.remove(Integer::valueOf(23));
    cout << set.contains(Integer::valueOf(23)) << endl;
    
    cout << set.contains(NULL) << endl;
    set.remove(NULL);
    cout << set.contains(NULL) << endl;


}

