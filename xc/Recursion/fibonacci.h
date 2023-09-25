#pragma once
#include<functional>

void fibPrint(function<int(int)> fib, int n) {
	for (int i = 1; i < n; i++) {
		if (i > 1) cout << ", ";
		cout << fib(i);
	}
	cout << endl;
}
/******************************************Fib**************************************************/
//重复计算多
//时间复杂度O(2ⁿ), 空间复杂度O(n)
int fib(int n) {
	if (n <= 2) return 1;
	return fib(n - 1) + fib(n - 2);
}

/******************************************Fib1**************************************************/
//数组存放计算结果，避免重复计算
//时间复杂度O(n),空间复杂度O(n)
int fib11(int* a, int n) {
	if (a[n] == 0) {
		a[n] = fib11(a, n - 1) + fib11(a, n - 2);
	}
	return a[n];
}

int fib1(int n) {
	if (n <= 2) return 1;
	int* a = new int[n + 1] {};
	a[1] = a[2] = 1;
	int v = fib11(a, n);
	delete[] a;
	return v;
}

/******************************************Fib2**************************************************/
//去递归
//时间复杂度O(n),空间复杂度O(n)
int fib2(int n) {
	if (n <= 2) return 1;
	int* a = new int[n + 1] {};
	a[1] = a[2] = 1;
	for (int i = 3; i <= n; ++i) {
		a[i] = a[i - 1] + a[i - 2];
	}
	int v = a[n];
	delete[] a;
	return v;
}

/******************************************Fib3**************************************************/
//时间复杂度O(n),空间复杂度O(1)
int fib3(int n) {
	if (n <= 2) return 1;
	int* a = new int[2] {};
	a[0] = a[1] = 1;
	for (int i = 3; i <= n; ++i) {
		a[i % 2] = a[(i - 1) % 2] + a[(i - 2) % 2];
	}
	int v = a[n % 2];
	delete[] a;
	return v;
}

/******************************************Fib4**************************************************/
//时间复杂度O(n),空间复杂度O(1)
int fib4(int n) {
	if (n <= 2) return 1;
	int* a = new int[2] {};
	a[0] = a[1] = 1;
	for (int i = 3; i <= n; ++i) {
		a[i & 1] = a[(i - 1) & 1] + a[(i - 2) & 1];
	}
	int v = a[n & 1];
	delete[] a;
	return v;
}
/******************************************Fib5**************************************************/
//时间复杂度O(n),空间复杂度O(1)
int fib5(int n) {
	if (n <= 2) return 1;
	int first = 1;
	int second = 1;
	for (int i = 3; i <= n; ++i) {
		second = first + second;
		first = second - first;
	}
	return second;
}
/******************************************Fib6**************************************************/
//线性代数解法：
//f(n) = c1x1ⁿ + c2x2ⁿ    其中c1 = 1/√5，  c2 = -1/√5， x1 = (1 + √5)/2, x2 = (1 - √5)/2
//f(n) = {[(1 + √5)/2]ⁿ - [(1 - √5)/2]ⁿ} /√5
//时间、空间复杂度可低至O(㏒n)
int fib6(int n) {
	double c = sqrt(5);
	return int((pow((1 + c) / 2, n) - pow((1 - c) / 2, n)) / c);
}

