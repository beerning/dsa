#pragma once
#include<iostream>
using namespace std;
#include <string>


template<size_t N> class Bitset;

template<size_t N>
Bitset<N> operator& (const Bitset<N>& lhs, const Bitset<N>& rhs); 
template<size_t N>  
Bitset<N> operator| (const Bitset<N>& lhs, const Bitset<N>& rhs);
template<size_t N>  
Bitset<N> operator^ (const Bitset<N>& lhs, const Bitset<N>& rhs);

template<size_t N> 
istream& operator >>(istream& is, Bitset<N>& rhs);
template<size_t N>
ostream& operator<<(ostream& os, const Bitset<N>& rhs);

template<size_t N>
class Bitset {
public:
	Bitset();
	~Bitset();
	bool operator[] (size_t pos) const;
	size_t count() const;
	size_t size() const;
	bool test(size_t pos) const;
	bool any() const;
	bool none() const;
	bool all() const noexcept;

	Bitset& set();
	Bitset& set(size_t pos, bool val = true);

	Bitset& reset();
	Bitset& reset(size_t pos);

	Bitset& flip();
	Bitset& flip(size_t pos);

	string to_string() const;
	unsigned long to_ulong() const;
	unsigned long long to_ullong() const;

	Bitset& operator&= (const Bitset& rhs);
	Bitset& operator|= (const Bitset& rhs);
	Bitset& operator^= (const Bitset& rhs);
	Bitset& operator<<= (size_t pos);
	Bitset& operator>>= (size_t pos);
	Bitset operator~() const;
	Bitset operator<<(size_t pos) const;
	Bitset operator>>(size_t pos) const;
	bool operator== (const Bitset& rhs) const;
	bool operator!= (const Bitset& rhs) const;

	friend Bitset<N> operator& <>(const Bitset<N>& lhs, const Bitset<N>& rhs);
	friend Bitset<N> operator| <>(const Bitset<N>& lhs, const Bitset<N>& rhs);
	friend Bitset<N> operator^ <>(const Bitset<N>& lhs, const Bitset<N>& rhs);

	//if declare stream operator << or >> here, conflict with shift operator  << or >> above

	/*friend istream& operator>> <>(istream& is, Bitset<N>& rhs);
	friend ostream& operator<< <>(ostream& os, const Bitset<N>& rhs);*/

private:
	size_t* bits;
	size_t bits_size;
	string itob(size_t x, bool isEnd = false) const;
	static const size_t SIZE = sizeof(size_t) * 8;
	void rangeCheck(size_t pos) const;
};

template<size_t N>
Bitset<N>::Bitset() {
	bits_size = (N + SIZE - 1) / SIZE;
	bits = new size_t[bits_size]{};
}

template<size_t N>
Bitset<N>::~Bitset() {
	delete[] bits;
}

template<size_t N>
inline bool Bitset<N>::operator[](size_t pos) const {
	rangeCheck(pos);
	return (bits[pos / SIZE] & 1ull << pos % SIZE) != 0;
}

template<size_t N>
inline size_t Bitset<N>::count() const {
	size_t count = 0;
	for (size_t i = 0; i < N; ++i) {
		//if (test(i) == true) count++;
		if ((*this)[i] == true) count++;
	}
	return count;
}

template<size_t N>
inline size_t Bitset<N>::size() const {
	return size_t(N);
}

template<size_t N>
inline bool Bitset<N>::test(size_t pos) const {
	rangeCheck(pos);
	return (bits[pos / SIZE] & 1ull << pos % SIZE) != 0;
}

template<size_t N>
inline bool Bitset<N>::any() const {
	bool any = false;
	for (size_t i = 0; i < bits_size; i++) {
		if (bits[i] != 0) {
			any = true;
			break;
		}
	}
	return any;
}

template<size_t N>
inline bool Bitset<N>::none() const {
	return !any();
}

template<size_t N>
inline bool Bitset<N>::all() const noexcept {
	bool all = true;
	size_t end = bits_size - 1;
	for (size_t i = 0; i < end; ++i) {
		if (bits[i] != UINTMAX_MAX) {
			all = false;
			break;
		}	
	}
	size_t remaider = N % SIZE;
	size_t n = remaider != 0 ? remaider : SIZE;
	size_t v = (size_t)exp2(--n) * 2 - 1;
	if (bits[end] != v) all = false;	
	return all;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::set() {
	for (size_t i = 0; i < N; ++i)
		set(i);
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::set(size_t pos, bool val) {
	rangeCheck(pos);
	size_t mask = 1ull << pos % SIZE;
	if (val == true)
		bits[pos / SIZE] |= mask;
	else
		bits[pos / SIZE] &= ~mask;
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::reset() {
	for (size_t i = 0; i < N; ++i)
		set(i, false);
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::reset(size_t pos) {
	set(pos, false);
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::flip() {
	for (size_t i = 0; i < N; ++i) 
		flip(i);
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::flip(size_t pos) {
	rangeCheck(pos);
	bits[pos / SIZE] ^= 1ull << pos % SIZE;
	return *this;
}

template<size_t N>
inline unsigned long Bitset<N>::to_ulong() const {
	const char* msg = "Too Large, Convertion Failed";
	for (size_t i = bits_size - 1; i > 0; --i) {
		_STL_ASSERT(bits[i] == 0, msg);
	}
	_STL_ASSERT(bits[0] <= UINT32_MAX, msg);

	return (unsigned long)bits[0];
}

template<size_t N>
inline unsigned long long Bitset<N>::to_ullong() const {
	const char* msg = "Too Large, Convertion Failed";
	for (size_t i = bits_size - 1; i > 0; --i) {
		_STL_ASSERT(bits[i] == 0, msg);
	}
	_STL_ASSERT(bits[0] <= UINT64_MAX, msg);

	return bits[0];
}


//bit operator member
template<size_t N>
inline Bitset<N>& Bitset<N>::operator&=(const Bitset& rhs) {
	for (size_t i = 0; i < bits_size; ++i) {
		bits[i] &= rhs.bits[i];
	}
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::operator|=(const Bitset& rhs) {
	for (size_t i = 0; i < bits_size; ++i) {
		bits[i] |= rhs.bits[i];
	}
	return *this;
}
template<size_t N>
inline Bitset<N>& Bitset<N>::operator^=(const Bitset& rhs) {
	for (size_t i = 0; i < bits_size; ++i) {
		bits[i] ^= rhs.bits[i];
	}
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::operator<<=(size_t pos) {
	if (pos >= N) {
		for (int i = 0; i < bits_size; ++i)
			bits[i] = 0;
	}
	string s = to_string();
	s.append(pos, '0');
	s = s.substr(pos, N);

	for (size_t i = 0; i < bits_size; ++i) {
		size_t loc = i == bits_size - 1 ? 0 : N - (i + 1) * SIZE;
		size_t len = i == bits_size - 1 ? N % SIZE : SIZE;
		string sub = s.substr(loc, len);
		
		size_t v = 0;
		for (int i = 0; i < len; ++i) {
			if (sub[i] == '1') v += (size_t)exp2(len - 1 - i);
		}
		bits[i] = v;
	}
	return *this;
}

template<size_t N>
inline Bitset<N>& Bitset<N>::operator>>=(size_t pos) {
	if (pos >= N) {
		for (int i = 0; i < bits_size; ++i)
			bits[i] = 0;
	}
	string s = to_string();
	s.insert(0, pos, '0');
	s = s.substr(0, N);
	for (size_t i = 0; i < bits_size; ++i) {
		size_t loc = i == bits_size - 1 ? 0 : N - (i + 1) * SIZE;
		size_t len = i == bits_size - 1 ? N % SIZE : SIZE;
		string sub = s.substr(loc, len);

		size_t v = 0;
		for (int i = 0; i < len; ++i) {
			if (sub[i] == '1') v += (size_t)exp2(len - 1 - i);
		}
		bits[i] = v;
	}
	return *this;
}

template<size_t N>
inline Bitset<N> Bitset<N>::operator~() const {
	Bitset<N> bitset;
	size_t end = bits_size - 1;
	for (size_t i = 0; i < end; ++i) {
		bitset.bits[i] = ~bits[i];
	}
	size_t idx = 0;
	size_t remaider = N % SIZE;
	bitset.bits[end] = bits[end];
	while (idx < remaider) {
		bitset.bits[end] ^= 1ull << idx;
		idx++;
	}
	return bitset;
}

template<size_t N>
inline Bitset<N> Bitset<N>::operator<<(size_t pos) const {
	Bitset<N> bitset;
	if (pos >= N) {
		for (int i = 0; i < bits_size; ++i)
			bitset.bits[i] = 0;
	}
	string s = to_string();
	s.append(pos, '0');
	s = s.substr(pos, N);

	for (size_t i = 0; i < bits_size; ++i) {
		size_t loc = i == bits_size - 1 ? 0 : N - (i + 1) * SIZE;
		size_t len = i == bits_size - 1 ? N % SIZE : SIZE;
		string sub = s.substr(loc, len);

		size_t v = 0;
		for (int i = 0; i < len; ++i) {
			if (sub[i] == '1') v += (size_t)exp2(len - 1 - i);
		}
		bitset.bits[i] = v;
	}
	return bitset;
}

template<size_t N>
inline Bitset<N> Bitset<N>::operator>>(size_t pos) const {
	Bitset<N> bitset;
	if (pos >= N) {
		for (int i = 0; i < bits_size; ++i)
			bitset.bits[i] = 0;
	}
	string s = to_string();
	s.insert(0, pos, '0');
	s = s.substr(0, N);
	for (size_t i = 0; i < bits_size; ++i) {
		size_t loc = i == bits_size - 1 ? 0 : N - (i + 1) * SIZE;
		size_t len = i == bits_size - 1 ? N % SIZE : SIZE;
		string sub = s.substr(loc, len);

		size_t v = 0;
		for (int i = 0; i < len; ++i) {
			if (sub[i] == '1') v += (size_t)exp2(len - 1 - i);
		}
		bitset.bits[i] = v;
	}
	return bitset;
}

template<size_t N>
inline bool Bitset<N>::operator==(const Bitset& rhs) const {
	bool equal = true;
	for (size_t i = 0; i < bits_size; ++i) {
		if (bits[i] != rhs.bits[i]) equal = false;
	}
	return equal;
}

template<size_t N>
inline bool Bitset<N>::operator!=(const Bitset& rhs) const {
	return !(*this == rhs);
}

template<size_t N>
inline string Bitset<N>::itob(size_t x, bool isEnd) const {
	string s;
	while (x != 0) {
		s.insert(0, x % 2 ? "1" : "0");
		x /= 2;
	}
	while (s.length() < (isEnd ? N % SIZE : SIZE))
		s.insert(0, "0");
	return s;
}

template<size_t N>
inline void Bitset<N>::rangeCheck(size_t pos) const {

	_STL_VERIFY(pos < N, "Bitset index outside range");
	/*try {
		if (pos >= N)
			throw exception("outBounds");
	}
	catch (const std::exception& e) {
		cout << "The pos(" << pos  << ") passed in is " << e.what() << endl;
		abort();
	}*/
}

template<size_t N>
inline string Bitset<N>::to_string() const {
	size_t size = bits_size;
	string s, str;
	size_t x;
	for (size_t i = 0; i < size; i++) {
		x = bits[i];
		str = i != size - 1 ? itob(x) : itob(x, true);
		s.insert(0, str);
	}
	return s;
}

//friend bit function
template<size_t N>
Bitset<N> operator& (const Bitset<N>& lhs, const Bitset<N>& rhs) {
	Bitset<N> ths;
	for (size_t i = 0; i < lhs.bits_size; ++i) {
		ths.bits[i] = lhs.bits[i] & rhs.bits[i];
	}
	return ths;
}

template<size_t N>
Bitset<N> operator| (const Bitset<N>& lhs, const Bitset<N>& rhs) {
	Bitset<N> ths;
	for (size_t i = 0; i < lhs.bits_size; ++i) {
		ths.bits[i] = lhs.bits[i] | rhs.bits[i];
	}
	return ths;
}

template<size_t N>
Bitset<N> operator^ (const Bitset<N>& lhs, const Bitset<N>& rhs) {
	Bitset<N> ths;
	for (size_t i = 0; i < lhs.bits_size; ++i) {
		ths.bits[i] = lhs.bits[i] ^ rhs.bits[i];
	}
	return ths;
}

//friend ios function
template<size_t N>
istream& operator>> (istream& is, Bitset<N>& rhs){
	return is;
}

template<size_t N>
ostream& operator <<(ostream& os, const Bitset<N>& rhs) {
	return os << rhs.to_string();
}