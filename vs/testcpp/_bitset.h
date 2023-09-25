#pragma once

#include <bitset>

namespace Bitset {

	void test() {
        bitset<20> bit;

        for (int i = bit.size() - 1; i >= 0; i--)
            bit.set(i);
        cout << bit << endl;
       /* cout << bit.size() << endl;
        cout << bit.count() << endl;
        for (int i = bit.size() - 1; i >= 0; --i)
            cout << bit[i] << " ";
        cout << endl;

        cout << "ulong: " << bit.to_ulong() << endl;
        cout << "ullong: " << bit.to_ullong() << endl;

        cout << bit.test(3) << "<-test(3), test(2)->" << bit.test(2) << endl;
        cout << bit.any() << endl;
        cout << bit.none() << endl;
        cout << bit.all() << endl;

        bit.reset(2);
        cout << bit << endl;


        bit.flip();
        cout << bit << endl;

        cout << bit.flip(0) << endl;*/

        bitset<8> a, b;
        a.set(3);
        b.set(5);
        auto c = a ^ b;
        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
	}
}