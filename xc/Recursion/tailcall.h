#pragma once

void test(int n) {
	if (n < 0) return;
	printf("test-%d\n", n);
	test(n - 1);
}
/***************************************阶乘*************************************************/
//未进行尾调用消除
int factorial0(int n) {
	if (n <= 1) return 1;
	return n * factorial0(n - 1);
}

//进行了尾调用消除
int factorial(int n, int result) {
	if (n <= 1) return result;
	return factorial(n - 1, n * result);
}

int factorial(int n) {
	return factorial(n, 1);
}
/***************************************斐波那契*************************************************/
//未进行尾调用消除
int fibonacci0(int n) {
	if (n <= 2) return 1;
	return fibonacci0(n - 1) + fibonacci0(n - 2);
}

//进行了尾调用消除
int fibonacci11(int n, int first, int second) {
	if (n <= 1) return first;
	return fibonacci11(n - 1, second, first + second);
}

int fibonacci1(int n) {
	return fibonacci11(n, 1, 1);
}