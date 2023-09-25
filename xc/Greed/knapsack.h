#pragma once
/**
* 1.有 n 件物品和一个总承重尾 W 的背包，每件物品重 wi, 价值 vi；
* 2.在保证总重量不超过 W 的情况下，将哪几件物品装入背包，使得价值最大；
* 3.每种物品只有一件，也就是每种物品只能选择0或1；因此称为0-1问题

* 如果采取贪心策略，有3种方案
* 1.价值主导：优先选择价值最高的物品
* 2.重量主导：优先选择重量最轻的物品
* 3.价值密度主导：优先选择价值密度（ = 价值/密度）最高的物品
 
* 假设背包最大承重150，7种物品价值重量信息如下：
*	编号	1		2		3		4		5		6		7
*	重量	35		30		60		50		40		10		25
*	价值	10		40		30		50		35		40		30
* 价值密度	0.29	1.33	0.5		1.0		0.88	4.0		1.2
*/

//物品：article, thing, goods, substance, ware, Stuff, Stuff


#include <vector>
#include <algorithm>

struct Stuff;
ostream& operator<<(ostream& os, const Stuff& s);
struct Stuff {
	int id;
	double weight;
	double value;
	double value_density;

	Stuff(int _id, double _weight, double _value) {
		id = _id;
		weight = _weight;
		value = _value;
		value_density = _value  / _weight;
	}
	friend ostream& operator<<(ostream& os, const Stuff& s);
};

ostream& operator<<(ostream& os, const Stuff& x){
	os << "(" << x.id << ", " << x.weight << ", " << x.value << ", " << x.value_density << ")";
	return os;
};

template<class _Pr>
void knapsack_core(Stuff* a, int n, _Pr _Pred) {
	vector<Stuff> v(a, a + n);
	sort(v.begin(), v.end(), _Pred);

#ifdef _DEBUG
	for (Stuff x : v)
		cout << x << " ";
	cout << endl;
#endif // _DEBUG

	int capacity = 150;	//背包容量
	double accweight = 0; //累计重量
	double worth = 0;	//总价值

	for (int i = 0; i < n && accweight <= capacity; ++i) {
		accweight += v[i].weight;
		if (accweight <= capacity) {
			worth += v[i].value;
			cout << v[i] << " ";
		}
		else {
			accweight -= v[i].weight;
		}
	}
	cout << ", ";
	cout << "总重量：" << accweight << ", 总价值" << worth << endl;
}

void knapsack() {

	Stuff stuffs[] = { Stuff{1, 35, 10 }, Stuff{2, 30, 40 }, Stuff{3, 60, 30 }, Stuff{4, 50, 50 }, Stuff{5, 40, 35 }, Stuff{6, 10, 40 }, Stuff{7, 25, 30 }};
	size_t n = sizeof(stuffs) / sizeof(Stuff);
	
//价值主导
	cout << "价值主导：" << endl;;
	struct {
		bool operator()(Stuff x, Stuff y) {
			return x.value > y.value;
		}
	}value_cmp;
	knapsack_core(stuffs, n, value_cmp);

//重量主导
	cout << "重量主导：" << endl;;
	struct {
		bool operator()(Stuff x, Stuff y) {
			return x.weight < y.weight;
		}
	}weight_cmp;
	knapsack_core(stuffs, n, weight_cmp);

//价值密度主导
	cout << "价值密度主导：" << endl;;
	struct {
		bool operator()(Stuff x, Stuff y) {
			return x.value_density > y.value_density;
		}
	}value_density_cmp;
	knapsack_core(stuffs, n, value_density_cmp);
}