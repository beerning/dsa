#pragma once

#include<iostream>
using namespace std;
#include<chrono>
template<class K, class V>
struct Node;
template<class K, class V>
ostream& operator<< (ostream& os, const Node<K, V>& node);

template<class K, class V>
struct Node {
	K key;
	V value;
	Node** nexts;
	int length;
	Node(K k, V v, int level) : key(k), value(v), length(level) {
		nexts = new Node * [level] {};
	}

	friend ostream& operator<< <>(ostream& os, const Node<K, V>& node);
};

template<class K, class V>
ostream& operator<< (ostream& os, const Node<K, V>& node) {
	return os << *node.key << ":" << *node.value;
}

template<class K, class V>
class skiplist;
template<class K, class V>
ostream& operator<< (ostream& os, const skiplist<K, V>& list);

template<class K, class V>
class skiplist {

public:
	skiplist() : skiplist(nullptr){}
	skiplist(int(*_comparator)(K, K));

	~skiplist();

	size_t size() const;
	bool empty() const;
	V get(K key) const;
	V put(K key, V value);
	V remove(K key);
	friend ostream& operator<< <>(ostream& os, const skiplist<K, V>& list);
private:
	static const double P;
	static const int  levelmax = 0x20;
	int level;
	size_t count;
	Node<K, V>* first;
	int(*comparator)(K, K);
	int compare(K k1, K k2)const;
	int randlevel() const;
};

template<class K, class V>
const double skiplist<K, V>::P = 0.25;

template<class K, class V>
skiplist<K, V>::skiplist(int(*_comparator)(K, K)) {
	_STL_VERIFY(_comparator != nullptr, "compare function pointer should be passed in");
	level = 0;
	count = 0;
	first = new Node<K, V>(nullptr, nullptr, levelmax);
	comparator = _comparator;
}

template<class K, class V>
skiplist<K, V>::~skiplist() {}

template<class K, class V>
inline size_t skiplist<K, V>::size() const {
	return count;
}

template<class K, class V>
inline bool skiplist<K, V>::empty() const {
	return count == 0;
}

template<class K, class V>
V skiplist<K, V>::get(K key) const {
	_STL_ASSERT(key != nullptr, "key can't be null");

	Node<K, V>* n = first;
	int cmp = -1;
	for (int i = level - 1; i >= 0; --i) {
		while (n->nexts[i] && (cmp = compare(key, n->nexts[i]->key)) > 0) {
			n = n->nexts[i];
		}
		if (cmp == 0) return n->nexts[i]->value;
	}
	return nullptr;
}

template<class K, class V>
V skiplist<K, V>::put(K key, V value) {
	_STL_ASSERT(key != nullptr, "key can't be null");
	Node<K, V> *n = first;
	Node<K, V>** prevs = new Node<K, V>*[level];
	int cmp = -1;
	for (int i = level - 1; i >= 0; --i) {
		while (n->nexts[i] && (cmp = compare(key, n->nexts[i]->key)) > 0) {
			n = n->nexts[i];
		}
		if (cmp == 0) {			
			V v = n->nexts[i]->value;
			n->nexts[i]->value = value;
			return v;
		}
		prevs[i] = n;
	}
	int newlevel = randlevel();
	Node<K, V>* node = new Node<K, V>(key, value, newlevel);

	for (int i = 0; i < newlevel; ++i) {
		if (i >= level) {
			first->nexts[i] = node;
		}
		else {
			node->nexts[i] = prevs[i]->nexts[i];
			prevs[i]->nexts[i] = node;
		}
	}
	count++;
	level = fmax(level, newlevel);
	delete prevs;
	return nullptr;
}

template<class K, class V>
V skiplist<K, V>::remove(K key) {
	_STL_ASSERT(key != nullptr, "key can't be null");

	Node<K, V>* n = first;
	int cmp = -1;
	bool exists = false;
	Node<K, V>** prevs = new Node<K, V>*[level];
	for (int i = level - 1; i >= 0; --i) {
		while (n->nexts[i] && (cmp = compare(key, n->nexts[i]->key)) > 0) {
			n = n->nexts[i];
		}
		prevs[i] = n;
		if (cmp == 0) exists = true;
	}
	if (!exists) return nullptr;

	Node<K, V>* node = n->nexts[0];
	V v = node->value;
	count--;

	for (int i = 0; i < node->length; ++i) {
		prevs[i]->nexts[i] = node->nexts[i];
	}

	//update level
	int h = level;
	while (--h >=0 && first->nexts[h] == nullptr) {
		level = h;
	}

	delete node;
	delete prevs;
	return v;
}

template<class K, class V>
int skiplist<K, V>::compare(K k1, K k2) const {
	return comparator(k1, k2);
}

template<class K, class V>
int skiplist<K, V>::randlevel() const {
	auto seed = chrono::system_clock::now().time_since_epoch().count(); //精确到nano，比time(null)计算的时间戳多出7位
	srand(seed);
	int level = 1;
	while (rand() % 100 < 25 && level < levelmax) {
		level++;
	}
	return level;
}


template<class K, class V>
ostream& operator<< (ostream& os, const skiplist<K, V>& list) {
	int i = list.level - 1;
	for (; i >= 0; --i) {
		Node<K, V>* node = list.first->nexts[i];
		cout << "level-" << i << ": ";
		while (node) {
			cout << *node << "  ";
			node = node->nexts[i];
		}
		cout << endl;
	}
	return os;
}
