//
//  Number.h
//  Map
//
//  Created by berning on 2015/6/1.
//

#ifndef Number_h
#define Number_h

#include "Object.h"

#define Number_t        "Number"
#define Character_t     "Character"
#define Short_t         "Short"
#define Integer_t       "Integer"
#define Long_t          "Long"
#define Float_t         "Float"
#define Double_t        "Double"

int compare2Number(id obj1, id obj2);

class Number : public Object{
public:
    Number(const char *isa, const char* superClass) : Object(isa, superClass){}
    Number() :  Object(Number_t, Object_t){}
};

class Character : public Number{
    char _val;
    int compare(char a, char b) const { return a - b;}
public:
    Character(char val) : Number(Character_t, Number_t), _val(val) {}
    
    static Character *valueOf(char v){return new Character(v);}
    char value() const {return _val;}
    
    string toString()const override{ return &_val;}
    int hashCode() override {return (int)_val;}
    
    int compareTo(id obj) override{
        if (strcmp(getClass(), obj->getClass()) == 0)
            return compare(_val, ((Character *)obj)->_val);
        return compare2Number(this, obj);
    }
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return false;
        return _val == ((Character *)obj)->_val;
    }
};

class Short : public Number{
    short _val;
    int compare(short a, short b) const { return a - b;}
public:
    Short(short val) : Number(Short_t, Number_t), _val(val) {}
    
    static Short *valueOf(short v){return new Short(v);}
    short value() const {return _val;}
    
    string toString()const override{ return to_string(_val);}
    int hashCode() override {return (int)_val;}

    int compareTo(id obj) override{
        if (strcmp(getClass(), obj->getClass()) == 0)
            return compare(_val, ((Short *)obj)->_val);
        return compare2Number(this, obj);
    }
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return false;
        return _val == ((Short *)obj)->_val;
    }
};


class Integer : public Number{
    int _val;
    int compare(int a, int b) const { return a > b ? 1 :  a < b ? -1 : 0;}
public:
    Integer(int val) : Number(Integer_t, Number_t), _val(val) {}
    
    static Integer *valueOf(int v){return new Integer(v);}
    int value() const {return _val;}

    string toString()const override{ return to_string(_val);}
    int hashCode() override {return _val;};

    int compareTo(id obj) override{
        if (strcmp(getClass(), obj->getClass()) == 0)
            return compare(_val, ((Integer *)obj)->_val);
        return compare2Number(this, obj);
    }
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return  false;
        return _val == ((Integer *)obj)->_val;
    }
};

class Long : public Number{
    long _val;
    int compare(long a, long b) const { return a > b ? 1 :  a < b ? -1 : 0;}
public:
    Long(long val) : Number(Long_t, Number_t), _val(val) {}
    
    static Long *valueOf(long v){return new Long(v);}
    long value() const {return _val;}

    string toString()const override{ return to_string(_val);}
    int hashCode() override {return int(_val ^ (_val >> 32 & 0xffffffff));}

    int compareTo(id obj) override{
        if (strcmp(getClass(), obj->getClass()) == 0)
            return compare(_val, ((Long *)obj)->_val);
        return compare2Number(this, obj);
    }
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return false;
        return _val == ((Long *)obj)->_val;
    }
};

class Float : public Number{
    float _val;
    int floatToRawIntBits(float value) const{
        int n = 0;
        float *p = (float *)&n;
        *p = value;
        return n;
    }
    
    /**
     * e.g
     * sqrt(n) (n  <  0)  NaN
     *  0 / 0.0  NaN
     */
    bool isNaN(float v) const{ return v != v;}
/**
 * Returns a representation of the specified floating-point value
 * according to the IEEE 754 floating-point "single format" bit
 * layout.
 *
 * <p>Bit 31 (the bit that is selected by the mask
 * {@code 0x80000000}) represents the sign of the floating-point
 * number.
 * Bits 30-23 (the bits that are selected by the mask
 * {@code 0x7f800000}) represent the exponent.
 * Bits 22-0 (the bits that are selected by the mask
 * {@code 0x007fffff}) represent the significand (sometimes called
 * the mantissa) of the floating-point number.
 *
 * <p>If the argument is positive infinity, the result is
 * {@code 0x7f800000}.
 *
 * <p>If the argument is negative infinity, the result is
 * {@code 0xff800000}.
 *
 * <p>If the argument is NaN, the result is {@code 0x7fc00000}.
 *
 * <p>In all cases, the result is an integer that, when given to the
 * {@link #intBitsToFloat(int)} method, will produce a floating-point
 * value the same as the argument to {@code floatToIntBits}
 * (except all NaN values are collapsed to a single
 * "canonical" NaN value).
 *
 * @param   value   a floating-point number.
 * @return the bits that represent the floating-point number.
 */
    int floatToIntBits(float value) const{
        if (isNaN(value)) return 0x7fc00000;
        return floatToRawIntBits(value);
    }
    
    int compare(float a, float b) const {
        if (a > b) return 1;
        if (a < b) return -1;

        int abits = floatToIntBits(a);
        int bbits = floatToIntBits(b);
        
        return abits > bbits ? 1 :  abits < bbits ? -1 : 0;
    }
public:
    Float(float val) : Number(Float_t, Number_t), _val(val) {}
    
    static Float *valueOf(float v){return new Float(v);}
    float value() const {return _val;}

    string toString()const override{ return to_string(_val);}
    int hashCode() override {return floatToIntBits(_val);}

    int compareTo(id obj) override{
        if (strcmp(getClass(), obj->getClass()) == 0)
            return compare(_val, ((Float *)obj)->_val);
        return compare2Number(this, obj);
    }
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return false;
        return _val == ((Float *)obj)->_val;
    }
};

class Double : public Number{
    double _val;
#ifdef _WIN64
    typedef long long LONG;
#define ZERO 0LL
#else
    typedef long  LONG;
#define ZERO 0L
#endif
    LONG doubleToRawLongBits(double value) const {
        LONG n = ZERO;
        double *p = (double *)&n;
        *p = value;
        return n;
    }
    
    bool isNaN(double v) const{ return (v != v);}
/**
 * Returns a representation of the specified floating-point value
 * according to the IEEE 754 floating-point "double
 * format" bit layout.
 *
 * <p>Bit 63 (the bit that is selected by the mask
 * {@code 0x8000000000000000L}) represents the sign of the
 * floating-point number. Bits
 * 62-52 (the bits that are selected by the mask
 * {@code 0x7ff0000000000000L}) represent the exponent. Bits 51-0
 * (the bits that are selected by the mask
 * {@code 0x000fffffffffffffL}) represent the significand
 * (sometimes called the mantissa) of the floating-point number.
 *
 * <p>If the argument is positive infinity, the result is
 * {@code 0x7ff0000000000000L}.
 *
 * <p>If the argument is negative infinity, the result is
 * {@code 0xfff0000000000000L}.
 *
 * <p>If the argument is NaN, the result is
 * {@code 0x7ff8000000000000L}.
 *
 * <p>In all cases, the result is a {@code long} integer that, when
 * given to the {@link #longBitsToDouble(long)} method, will produce a
 * floating-point value the same as the argument to
 * {@code doubleToLongBits} (except all NaN values are
 * collapsed to a single "canonical" NaN value).
 *
 * @param   value   a {@code double} precision floating-point number.
 * @return the bits that represent the floating-point number.
 */

    LONG doubleToLongBits(double value) const {
        if (isNaN(value)) return 0x7ff8000000000000L;
        return doubleToRawLongBits(value);
    }

    int compare(double a, double b) const {
        if (a > b) return 1;
        if (a < b) return -1;
    
        LONG abits = doubleToLongBits(a);
        LONG bbits = doubleToLongBits(b);
        
        return abits > bbits ? 1 :  abits < bbits ? -1 : 0;
    }

public:
    Double(double val) : Number(Double_t, Number_t), _val(val) {}
    
    static Double *valueOf(double v){return new Double(v);}
    double value() const {return _val;}

    string toString()const override{ return to_string(_val);}
    int hashCode() override{
        LONG bits = doubleToLongBits(_val);
        return int(bits ^ (bits >> 32 & 0xffffffff));
    }

    int compareTo(id obj) override{
        if (strcmp(getClass(), obj->getClass()) == 0)
            return compare(_val, ((Double *)obj)->_val);
        return compare2Number(this, obj);
    }
    bool equals(id obj) const override {
        if (this == obj) return true;
        if (obj == NULL || strcmp(this->getClass(), obj->getClass()) != 0) return false;
        return _val == ((Double *)obj)->_val;
    }
};

int compare2Number(id obj1, id obj2){
    double v1 = 0.0;
    double v2 = 0.0;
    const char *cls1 = obj1->getClass();
    const char *cls2 = obj2->getClass();
    
    if (strcmp(cls1, Character_t) == 0) v1 = ((Character *)obj1)->value();
    else if (strcmp(cls1, Short_t) == 0) v1 = ((Short *)obj1)->value();
    else if (strcmp(cls1, Integer_t) == 0) v1 = ((Integer *)obj1)->value();
    else if (strcmp(cls1, Long_t) == 0) v1 = ((Long *)obj1)->value();
    else if (strcmp(cls1, Float_t) == 0) v1 = ((Float *)obj1)->value();
    else if (strcmp(cls1, Double_t) == 0) v1 = ((Double *)obj1)->value();

    if (strcmp(cls2, Character_t) == 0) v2 = ((Character *)obj2)->value();
    else if (strcmp(cls2, Short_t) == 0) v2 = ((Short *)obj2)->value();
    else if (strcmp(cls2, Integer_t) == 0) v2 = ((Integer *)obj2)->value();
    else if (strcmp(cls2, Long_t) == 0) v2 = ((Long *)obj2)->value();
    else if (strcmp(cls2, Float_t) == 0) v2 = ((Float *)obj2)->value();
    else if (strcmp(cls2, Double_t) == 0) v2 = ((Double *)obj2)->value();
    
    return v1 > v2 ? 1 :  v1 < v2 ? -1 : 0;
}


#endif /* Number_h */
