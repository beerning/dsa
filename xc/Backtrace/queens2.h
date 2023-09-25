#pragma once
namespace blue {
	class Queens {
		int length;
		int* queens;
		int ways;

		int cols;
		int leftTop;
		int rightTop;

		void log() {
#ifdef _DEBUG
			for (int row = 0; row < length; ++row) {
				for (int col = 0; col < length; ++col) {
					string q = queens[row] == col ? "Q" : ".";
					cout << q << " ";
				}
				cout << endl;
			}
			cout << endl;
#endif //_DEBUG
		}
	public:
		int getWays() { return ways; }
		Queens(int n) : ways(0), length(n) {
			cols = 0;
			leftTop = 0;
			rightTop = 0;
			queens = new int[n] {};
		}
		~Queens() {
			delete[] queens;
		}

		void place(int row) {
			if (row == length) {
				ways++;
				log();
				return;
			}
			for (int col = 0; col < length; ++col) {
				int cv = 1 << col;
				if (cols & cv) continue;
				int lt = 1 << (row - col + length - 1);
				if (leftTop & lt) continue;
				int rt = 1 << (row + col);
				if (rightTop & rt) continue;

				queens[row] = col;

				cols |= cv;
				leftTop |= lt;
				rightTop |= rt;
				place(row + 1);
				cols &= ~cv;
				leftTop &= ~lt;
				rightTop &= ~rt;
			}
		}

	};

	void queens(int n) {
		if (n < 1) return;
		Queens q(n);
		q.place(0);
		cout << n << "皇后共有" << q.getWays() << "种摆法" << endl;
	}
}
