#pragma once
//#include <algorithm>
//思想：1、选定一个基准点，经过若干次交换后，基准点左侧的元素都小于基准元素，基准点右侧的元素都大于基准元素；2、对基准点左右两侧的子序列分别进行第一步操作，直到基准点两侧的序列都只剩一个为止
int patition(int* a, int leading, int trailing) {
	int pivot = a[leading];

	while (leading < trailing) {
		while (leading < trailing && a[trailing] >= pivot)
			--trailing;
		swap(a[leading], a[trailing]);

		while (leading < trailing && a[leading] <= pivot)
			++leading;
		swap(a[leading], a[trailing]);
	}
	
	return leading;
}

void quicksort(int* a, int leading, int trailing) {
	if (trailing - leading < 2) return;

	int pivot = patition(a, leading, trailing - 1);
	quicksort(a, leading, pivot);
	quicksort(a, pivot + 1, trailing);
}


/***********************************************************************************************************************
*****************************				     C++ STL						****************************************
***********************************************************************************************************************/
#include <algorithm>
#include <random>
#include <chrono>

void arraytraversal(int* a, int n, string title = "") {
	if (title != "")
		cout << "【" << title << "】" << endl;
	for (int i = 0; i < n; ++i) {
		if (i > 0) cout << ", ";
		cout << a[i];
	}
	cout << endl;
}


int uniform_random(int n) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0, n - 1);
	return distribution(generator);
}

void shuffle(int *a, int n) {
	//auto seed = time(NULL); //在循环多多次调用，会出现重复，时间戳只精确到秒，一秒调用多次不准确
	auto seed = chrono::system_clock::now().time_since_epoch().count(); //精确到nano，比time(null)计算的时间戳多出7位
	srand(seed);
	for (int i = n - 1; i > 0; --i) {
		int x = rand() % i;
		swap(a[x], a[i]);
	}
}

void shuffle1(int* a, int n) {
	auto seed = chrono::system_clock::now().time_since_epoch().count(); 
	default_random_engine generator(seed);
	for (int i = n - 1; i > 0; --i) {
		uniform_int_distribution<int> distribution(0, i - 1);
		auto x = distribution(generator);
		swap(a[x], a[i]);
	}
}