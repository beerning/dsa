#pragma once
#include <vector>
#include <algorithm>

void coinchage_core1(int *a, size_t n) {
	vector<int> v(a, a + n);
	sort(v.begin(), v.end());

	int change = 41;
	int accumulation = 0;
	int count = 0;

	for (int i = n - 1; i >= 0 && accumulation <= change; ) {
		accumulation += v[i];
		
		while (accumulation > change && i > 0) {
			accumulation -= v[i];
			accumulation += v[--i];
		}
		
		if (accumulation > change) {
			accumulation -= v[i];
			break;
		}
		cout << v[i] << " ";
		count++;
	}
	cout << endl;
	cout << "共用了" << count << "枚硬币，共" << accumulation << "分" << endl;
}

void coinchage_core(int* a, size_t n) {
	vector<int> v(a, a + n);

	int change = 41;
	int count = 0;
	int accumulation = 0;

//正序
	sort(v.begin(), v.end());
	int idx = n - 1;

	while (idx >= 0) {
		if (change < v[idx]) {
			idx--;
			continue;
		}

		change -= v[idx];
		accumulation += v[idx];
		count++;
		cout << v[idx] << " ";
	}

//逆序
	/*struct {
		bool operator()(int x, int y) {
			return x > y;
		}
	}coincmp;
	sort(v.begin(), v.end(), coincmp);
	int idx = 0;

	while (idx < n) {
		if (change < v[idx]) {
			idx++;
			continue;
		}

		change -= v[idx];
		accumulation += v[idx];
		count++;
		cout << v[idx] << " ";
	}*/

	cout << endl;
	cout << "共用了" << count << "枚硬币，共" << accumulation << "分" << endl;
}

void coinchage_core3(int* a, size_t n) {
	vector<int> v(a, a + n);
	sort(v.begin(), v.end());

	int change = 41;
	int count = 0;
	int accumulation = 0;

	for (int i = n - 1; i >= 0; --i) {
		if (change < v[i]) {
			continue;
		}
		change -= v[i];
		accumulation += v[i];
		count++;
		cout << v[i] << " ";

		i = n;
	}

	cout << endl;
	cout << "共用了" << count << "枚硬币，共" << accumulation << "分" << endl;
}

void coinchange() {
	int c[] = { 25, 5, 10, 1 };
	size_t n = sizeof(c) / sizeof(int);
	coinchage_core(c, n);

	cout << "--------------------------------" << endl;
	int c1[] = { 25, 5, 20, 1 };            
	size_t n1 = sizeof(c1) / sizeof(int);
	coinchage_core(c1, n1);			//输出：25，5，5，5，1；实际20， 20， 1是最优解
}