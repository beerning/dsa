#ifndef Person_h
#define Person_h

class Person{
    string _name;
    int _age;
public:
    Person() : _name("Jack"), _age(20){}
    Person(int age, string name): _name(name), _age(age){}
    
    void setName(string name){_name = name;}
    void setAge(int age){_age = age;}
    
    string name() const {return _name;}
    int age() const {return _age;}
    
    friend ostream & operator<< (ostream &os, const Person &p);
    friend ostream & operator<< (ostream &os, const Person *p);
    
    friend int operator- (const Person &p1, const Person &p2);
    friend bool operator== (const Person &p1, const Person &p2);
    friend bool operator! (const Person &p);
    
    friend string to_string(Person *p);
    friend string to_string(Person &p);
};

int operator- (const Person &p1, const Person &p2){
    return p1._age - p2._age;
}
bool operator== (const Person &p1, const Person &p2){
    return p1._name == p2._name && p1._age == p2._age;
}
bool operator! (const Person &p){
    return p._name == "" && p._age == 0;
}

ostream & operator<< (ostream &os, const Person *p){
    os << p->_name << "(" << p->_age << ")";
    return os;
}
ostream & operator<< (ostream &os, const Person &p){
    os << p._name << "(" << p._age << ")";
    return os;
}

string to_string(Person &p){
    return p._name + "(" + to_string(p._age) + ")";
}

string to_string(Person *p){
    return p->_name + "(" + to_string(p->_age) + ")";
}

#endif /* Person_h */
