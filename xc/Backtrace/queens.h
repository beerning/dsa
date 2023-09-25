#pragma once
namespace red{
	class Queens {
		int length;
		int* queens;
		int ways;

		bool isValid(int row, int col) {
			for (int i = 0; i < row; ++i) {
				if (queens[i] == col || row - i == abs(col - queens[i])) return false;
			}
			return true;
		}

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
			queens = new int[n] {};
		}
		~Queens() { delete[] queens; }

		void place0(int row);
		void place(int row);

	};

	void queens(int n) {
		if (n < 1) return;
		Queens q(n);
		q.place(0);
		cout << n << "皇后共有" << q.getWays() << "种摆法" << endl;
	}

	void Queens::place(int row) {
		if (row == length) {
			ways++;
			log();
			return;
		}
		for (int col = 0; col < length; ++col) {//扫描列
			if (isValid(row, col) == true) {
				queens[row] = col;
				place(row + 1);
			}
		}
	}
	void Queens::place0(int row) {
		if (row == length) {
			ways++;
			log();
			return;
		}
		bool valid = true;
		for (int col = 0; col < length; ++col) {//扫描列
			valid = true;
			for (int i = 0; i < row; ++i) {//扫描前面的皇后是否在该列，或前面的皇后所在的斜线是否经过当前行列（坐标）
				if (queens[i] == col || row - i == abs(col - queens[i])) {
					valid = false;
					break;
				}
			}
			if (valid == true) {
				queens[row] = col;
				place0(row + 1);
			}
		}
	}
}
