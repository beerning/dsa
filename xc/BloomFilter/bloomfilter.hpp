#pragma once
#include <iostream>
using namespace std;
#include "Bitset.hpp"
#include "hashCode.hpp"

template<class T>
class boomfilter {
	size_t* bits;
	static const size_t SIZE = sizeof(size_t) * 8;
	size_t bits_size, binaries;
	int hashes;
	bool set(size_t pos);
	bool operator[](size_t pos) const;
public:
	void print() {
		cout << "bits_size = " << bits_size << endl;
		cout << "banaried = " << binaries << endl;
		cout << "hashes = " << hashes << endl;
	}
	boomfilter(size_t n, double p);
	bool put(T v);
	bool contains(T v);
};

template<class T>
boomfilter<T>::boomfilter(size_t n, double p) {
	_STL_VERIFY(n > 0, "param n should be greater than 0");
	_STL_VERIFY(p > 0 && p < 1, "param p should between 0 and 1");

	double ln2 = log(2);
	binaries =  size_t(- (n * log(p) / (ln2 * ln2)));
	hashes = int(binaries / n * ln2);
	bits_size = (binaries + SIZE - 1) / SIZE;
	bits = new size_t[bits_size]{};
}

template<class T>
inline bool boomfilter<T>::set(size_t pos) {
	size_t mask = 1ull << pos % SIZE;
	size_t idx = pos / SIZE;
	size_t v = bits[idx];
	bits[idx] |= mask;
	return (v & mask) == 0;
}

template<class T>
inline bool boomfilter<T>::operator[](size_t pos) const {
	return (bits[pos / SIZE] & 1ull << pos % SIZE) != 0;
}

template<class T>
bool boomfilter<T>::put(T v) {
	int h1 = hashCode(v);
	int h2 = h1 >> 16 & 0xffff;  //equivalent to (h1 >>> 16) in java

	bool res = false;
	for (int i = 1; i <= hashes; i++) {
		int combineHash = h1 + (i * h2);
		if (combineHash < 0)
			combineHash = ~combineHash;
		size_t pos = combineHash % binaries;
		if (set(pos)) res = true;
	}
	return res;
}

template<class T>
bool boomfilter<T>::contains(T v) {
	int h1 = hashCode(v);
	int h2 = h1 >> 16 & 0xffff;
	
	for (int i = 1; i <= hashes; i++) {
		int combineHash = h1 + (i * h2);
		if (combineHash < 0)
			combineHash = ~combineHash;
		size_t pos = combineHash % binaries;
		if ((*this)[pos] == false) return false;
	}
	return true;
}
