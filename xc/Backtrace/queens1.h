#pragma once
namespace green {
	class Queens {
		int length;
		int* queens;
		int ways;

		bool* cols;
		bool* leftTop;
		bool* rightTop;

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

			cols = new bool[n] {};
			int size = (n << 1) - 1;
			leftTop = new bool[size] {};
			rightTop = new bool[size] {};
		}
		~Queens() { 
			delete[] queens; 
			delete[] cols;
			delete[] leftTop;
			delete[] rightTop;
		}

		void place(int row) {
			if (row == length) {
				ways++;
				log();
				return;
			}
			for (int col = 0; col < length; ++col) {
				if (cols[col] == true) continue;
				int lt = row - col + length - 1;
				if (leftTop[lt] == true) continue;
				int rt = row + col;
				if (rightTop[rt] == true) continue;

				queens[row] = col;
				cols[col] = leftTop[lt] = rightTop[rt] = true;
				place(row + 1);
				cols[col] = leftTop[lt] = rightTop[rt] = false;

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
