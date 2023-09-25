#pragma once
#include <vector>

//O(n³)
int max_continous_subarray_core1(int *a, vector<int *> &v, int n) {
	if (a == NULL || n == 0) return 0;
	int max = INT_MIN, sum;
	
	//max
	for (int begin = 0; begin < n; ++begin) {
		for (int end = begin; end < n; ++end) {
			sum = 0;
			for (int i = begin; i <= end; ++i) {
				sum += a[i];
			}
			max = fmax(max, sum);
			
		}
	}

	//区间
	for (int begin = 0; begin < n; ++begin) {
		for (int end = begin; end < n; ++end) {
			sum = 0;
			for (int i = begin; i <= end; ++i) {
				sum += a[i];
			}
			if (sum == max) {
				int* range = new int[2] { begin, end };
				v.push_back(range);
			}
		}
	}
	return max;
}

//优化：O(n²)
int max_continous_subarray_core2(int* a, vector<int *> &v, int n) {
	if (a == NULL || n == 0) return 0;
	int max = INT_MIN, sum;

	for (int begin = 0; begin < n; ++begin) {
		sum = 0;
		for (int end = begin; end < n; ++end) {
			sum += a[end];
			max = fmax(max, sum);
			
		}
	}

	for (int begin = 0; begin < n; ++begin) {
		sum = 0;
		for (int end = begin; end < n; ++end) {
			sum += a[end];
			if (sum == max) {
				int* range = new int[2] { begin, end };
				v.push_back(range);
			}
		}
	}
	return max;
}

//分治 O(nlogn)
int max_continous_subarray_dc(int* a, int begin, int end) {
	if (end - begin < 2) return a[begin];
	int mid = begin + ((end - begin) >> 1);

	int lmax = INT_MIN;
	int lsum = 0;
	for (int i = mid - 1; i >= begin; --i) {
		lsum += a[i];
		lmax = fmax(lmax, lsum);
	}

	int rmax = INT_MIN;
	int rsum = 0;
	for (int i = mid; i < end; ++i) {
		rsum += a[i];
		rmax = fmax(rmax, rsum);
	}
	return fmax(lmax + rmax, fmax(max_continous_subarray_dc(a, begin, mid), max_continous_subarray_dc(a, mid, end)));
}

//range
int max_continous_subarray_range(int* a, vector<int*>& v, int max, int begin, int end) {
	if (end - begin < 2) {
		if (a[begin] == max) {
			int* range = new int[2] {begin, begin};
			v.push_back(range);
		}
		return a[begin];
	}
	int mid = begin + ((end - begin) >> 1);
	int lmax = INT_MIN;
	int lsum = 0, li;
	for (int i = mid - 1; i >= begin; --i) {
		lsum += a[i];
		if (lsum >= lmax) li = i;
		lmax = fmax(lmax, lsum);
	}

	int rmax = INT_MIN;
	int rsum = 0, ri;
	for (int i = mid; i < end; ++i) {
		rsum += a[i];
		if (rsum >= rmax) ri = i;
		rmax = fmax(rmax, rsum);
	}

	if (lmax + rmax == max) {
		int* range = new int[2] {li, ri};
		v.push_back(range);
	}
	return fmax(lmax + rmax, fmax(max_continous_subarray_range(a, v, max, begin, mid), max_continous_subarray_range(a, v, max, mid, end)));
}


int max_continous_subarray_core(int* a, vector<int *> &v, int n) {
	if (a == NULL || n == 0) return 0;
	int max = max_continous_subarray_dc(a, 0, n);
	max_continous_subarray_range(a, v, max, 0, n);
	return max;
}

void max_continous_subarray() {
	int a[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	//int a[] = { 1, -1, 1, 1, -1 };
	//int a[] = {3, 3, -6, 6};
	//int a[] = { 5, -10, 3, 2, -6, 4, 1, -5, 2, 3};
	size_t n = sizeof(a) / sizeof(int);
	vector<int *> v;
    int max = max_continous_subarray_core(a, v, n);
	
	//区间
	cout << "最大子序列和为" << max << ", 位于";
	for (int i = 0; i < v.size(); ++i) {
		if (i > 0) cout << ", ";
		cout << "[" << v[i][0] << ", " << v[i][1] << "]" ;
	}
	cout << "之间." << endl;
	
}