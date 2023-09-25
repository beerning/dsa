#pragma once

//n个台阶，一步可以1个或2个台阶
int climbStairs12(int n) {
	if (n <= 2) return n;
	return climbStairs12(n - 1) + climbStairs12(n - 2);
}

//n个台阶，一步可以1个、2个或3个台阶
int climbStairs123(int n) {
	if (n <= 2) return n;
	if (n == 3) return 4;
	return climbStairs123(n - 1) + climbStairs123(n - 2) + +climbStairs123(n - 3);
}


int climbStairs13(int n) {
	if (n <= 2) return 1;
	if (n == 3) return 2;
	return climbStairs13(n - 1) + climbStairs13(n - 3);
}


//类似的，如果一步可以1、2、3、4个台阶，只需算出第一步走的台阶有几种可能即可
//优化思路：和fib优化思路相似
int climbStairs12_12(int n) {
	if (n <= 2) return n;
	int first = 1;
	int second = 2;
	for (int i = 3; i <= n; ++i) {
		second = first + second;
		first = second - first;
	}
	return second;
}