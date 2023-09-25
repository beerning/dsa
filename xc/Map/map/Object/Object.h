//
//  Object.h
//  Map
//
//  Created by berning on 2015/6/1.
//

#ifndef Object_h
#define Object_h

#define Object_t    "Object"
#define nil         "NULL"

typedef class Object * id;

class Object{
protected:
    const char *_isa;
    const char *_superClass;
public:
    Object(const char *isa, const char * superClass) : _isa(isa), _superClass(superClass) {}
    Object() : Object(Object_t, nil){}
    
    virtual string toString() const{
        return "obj_" + to_string((unsigned long long)this);}
    virtual int hashCode() {return 0x0;}
    
    virtual int compareTo(id obj) {return 0;};
    static bool equals(id obj1, id obj2) {return obj1 == obj2 || (obj1 != NULL && obj1->equals(obj2));}
    virtual bool equals(id obj) const {return this == obj;}
    
    const char *getClass() const {return _isa;}
    const char * superClass() const {return _superClass;}
};


#endif /* Object_h */
