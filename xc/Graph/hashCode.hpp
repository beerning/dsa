//
//  hashCode.h
//  algorithm
//
//  Created by berning on 2015/10/13.
//

#ifndef hashCode_hpp
#define hashCode_hpp
#include <string>

template<class T>
int hashCode(T key) {
    return 0;
}

template<class T>
bool equals(T v1, T v2){
    return false;
}

#pragma mark - int8_t
template<>
int hashCode<int8_t>(int8_t key){
    return (int)key;
}

template<>
bool equals<int8_t>(int8_t v1, int8_t v2){
    return v1 == v2;
}

#pragma mark - int16_t
template<>
int hashCode<int16_t>(int16_t key){
    return (int)key;
}
template<>
bool equals<int16_t>(int16_t v1, int16_t v2){
    return v1 == v2;
}

#pragma mark - int32_t
template<>
int hashCode<int32_t>(int32_t key){
    return key;
}
template<>
bool equals<int32_t>(int32_t v1, int32_t v2){
    return v1 == v2;
}

#pragma mark - long
#ifdef _WIN64
template<>
int hashCode<long>(long key) {
    return int(key);
}
#else
template<>
int hashCode<long>(long key) {
    return int(key ^ (key >> 32 & 0xffffffff));;
}
#endif // _WIN64

template<>
bool equals<long>(long v1, long v2){
    return v1 == v2;
}

#pragma mark - long long
template<>
int hashCode<long long>(long long key) {
    return int(key ^ (key >> 32 & 0xffffffff));;
}

template<>
bool equals<long long>(long long v1, long long v2) {
    return v1 == v2;
}

//unsigned member
#pragma mark - uint8_t
template<>
int hashCode<uint8_t>(uint8_t key) {
    return (int)key;
}

template<>
bool equals<uint8_t>(uint8_t v1, uint8_t v2) {
    return v1 == v2;
}

#pragma mark - uint16_t
template<>
int hashCode<uint16_t>(uint16_t key) {
    return (int)key;
}
template<>
bool equals<uint16_t>(uint16_t v1, uint16_t v2) {
    return v1 == v2;
}

#pragma mark - uint32_t
template<>
int hashCode<uint32_t>(uint32_t key) {
    return (int)key;
}
template<>
bool equals<uint32_t>(uint32_t v1, uint32_t v2) {
    return v1 == v2;
}

#pragma mark - unsigned long
#ifdef _WIN64
template<>
int hashCode<unsigned long>(unsigned long key) {
    return int(key);
}
#else
template<>
int hashCode<unsigned long>(unsigned long key) {
    return int(key ^ (key >> 32));
}
#endif // _WIN64

template<>
bool equals<unsigned long>(unsigned long v1, unsigned long v2) {
    return v1 == v2;
}

#pragma mark - unsigned long long
template<>
int hashCode<unsigned long long>(unsigned long long key) {
    return int(key ^ (key >> 32));
}
template<>
bool equals<unsigned long long>(unsigned long long v1, unsigned long long v2) {
    return v1 == v2;
}


//
#pragma mark - float
int floatToRawIntBits(float value){
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
bool isNaN(float v) { return v != v;}
int floatToIntBits(float value){
    if (isNaN(value)) return 0x7fc00000;
    return floatToRawIntBits(value);
}

template<>
int hashCode<float>(float key){
    return floatToIntBits(key);
}

template<>
bool equals<float>(float v1, float v2){
    return v1 == v2;
}

#pragma mark - double

#ifdef _WIN64
typedef long long LONG;
#define ZERO 0LL
#else
typedef long  LONG;
#define ZERO 0L
#endif

LONG doubleToRawLongBits(double value) {
    LONG n = ZERO;
    double *p = (double *)&n;
    *p = value;
    return n;
}

bool isNaN(double v) { return (v != v);}

LONG doubleToLongBits(double value){
    if (isNaN(value)) return 0x7ff8000000000000L;
    return doubleToRawLongBits(value);
}
template<>
int hashCode<double>(double key){
    LONG bits = doubleToLongBits(key);
    return int(bits ^ (bits >> 32 & 0xffffffff));
}

template<>
bool equals<double>(double v1, double v2){
    return v1 == v2;
}

#pragma mark - string
template<>
int hashCode<string> (string key) {
    size_t len = key.size();
    int h = 0;
    for (size_t i = 0; i < len; i++){
        char c = key[i];
        h = (h << 5) - h + c;
    }
    return h;
}

template<>
bool equals<string>(string v1, string v2){
    return v1 == v2;
}

#endif /* hashCode_h */
