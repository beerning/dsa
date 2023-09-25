#pragma once
#include <string>
void move(int i, string from, string to) {
	cout << "第" << i << "个盘子从" << from << "移动到" << to << endl;
}

void hanoi(int n, string p1, string p2, string p3) {
	if (n <= 1) {
		move(n, p1, p3);
		return;
	}
	hanoi(n - 1, p1, p3, p2);
	move(n, p1, p3);
	hanoi(n - 1, p2, p1, p3);
}