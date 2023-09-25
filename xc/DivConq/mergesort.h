#pragma once

//思想：把一个序列不断分割为两个子序列，直到不能再分割；把两个子序列合并为一个序列，直到只有一个序列为止

void merge(int *a, int *output, int begin, int mid, int end) {
	int li = 0, le = mid - begin;
	int ri = mid, re = end;
	int ai = begin;

	for (int i = li; i < le; ++i) {
		output[i] = a[begin + i];
	}

	while (li < le) {
		if (ri < re && a[ri] < output[li]) {
			a[ai++] = a[ri++];
		}
		else {
			a[ai++] = output[li++];
		}
	}
}

void mergesort(int *a, int *output, int begin, int end) {
	if (end - begin < 2) return;

	int mid = begin + ((end - begin) >> 1);
	mergesort(a, output, begin, mid);
	mergesort(a, output, mid, end);
	merge(a, output, begin, mid, end);
}