#pragma once
#include <vector>
#include <algorithm>
//海盗打劫了一条商船，船上装满了各种价值连城的古董
//海盗船的容量为W = 30,每一件古董的重量为ωi = {3, 5, 4, 10, 7, 14, 2, 11}
//问题：怎么把尽可能数量多的古董装上船

void pirate_core(int *a, int n){
	vector<int> weights(a, a + n);
	sort(weights.begin(), weights.end());

	int capacity = 30;
	int weight = 0;
	int count = 0;

	for (int i = 0; i < n && weight <= capacity; ++i) {
		weight += weights[i];
		if (weight <= capacity) {
			count++;
		}
		else {
			weight -= weights[i];
			break;
		}
	}
	cout << "一共装了" << count << "件古董，总重" << weight << endl;
}

void pirate(){
	int a[] = {3, 5, 4, 10, 7, 14, 2, 11};
	int n = sizeof(a) / sizeof(int);
	pirate_core(a, n);
}