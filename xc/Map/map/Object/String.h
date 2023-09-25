//
//  String.h
//  Map
//
//  Created by berning on 2015/6/1.
//

#ifndef String_h
#define String_h

#include "Object.h"

class String : public Object{
    const char *_val;
    int _hash;
    bool _hashIsZero;
    
    int hashCode (const char *s) const{
        unsigned long len = strlen(s);
        int h = 0;
        for (unsigned long i = 0; i < len; i++){
            char c = s[i]; 
            h = (h << 5) - h + c;
        }
        return h;
    }
    
    int compare(const char *v1, const char *v2) const{ return strcmp(v1, v2);}
public:
    String(const char *val) : Object("String", "Object"), _val(val), _hash(0), _hashIsZero(false) {}
    
    unsigned long length() const {return strlen(_val);}
    
    static String *valueOf(const char *v){return new String(v);}
    const char *value() const {return _val;}
    
    string toString() const override{string s = _val; return s;}
    int hashCode() override{
        int h = _hash;
        if (h == 0 && !_hashIsZero){
            h = hashCode(_val);
            if (h == 0){
                _hashIsZero = true;
            }else{
                _hash = h;
            }
        }
        return h;
    }
    
    int compareTo(id obj) const {return compare(_val, ((String *)obj)->_val);};
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return false;
        return strcmp(_val, ((String *)obj)->_val) == 0;
    }
    
    String *append(String *s){
        size_t len = strlen(_val) + strlen(s->_val) + 1;
        char *vol = new char[len];
#ifdef _WIN64
        strcpy_s(vol, len, _val);
        strcat_s(vol, len, s->_val);
#else
        strcat(vol, _val);
        strcat(vol, s->_val);
#endif
        _val = vol;
        return this;
    }
    
    String& append(String &s){
        size_t len = strlen(_val) + strlen(s._val) + 1;
        char *vol = new char[strlen(_val) + strlen(s._val)];
#ifdef _WIN64
        strcpy_s(vol, len, _val);
        strcat_s(vol, len, s._val);
#else
        strcat(vol, _val);
        strcat(vol, s._val);
#endif
        _val = vol;
        return *this;
    }
};
#endif /* String_h */
