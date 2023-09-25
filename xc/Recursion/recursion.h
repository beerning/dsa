#pragma once
#include<stack>                             

                                            //       |      log      |      |
                                            //       | n = 1, v = 10 | ____ | 栈帧
                                            //       |      log      |   
void log(int n) {                           //       | n = 2, v = 12 |
                                            //       |      log      |               
    if (n < 1) return;                      //       | n = 3, v = 13 |             
    log(n - 1);                             //       |      log      |
    int v = n + 10;                         //       | n = 4, v = 14 |  
    cout << v << endl;                      //       |      main     |     
}                                           //       | argc, argv    |       
                                            //       └-------------┘     
/*************************************************递归转非递归*******************************************************/
class Frame {
    int n;
    int v;
public:
    Frame(int _n, int _v) : n(_n), v(_v) {}
    int getV() { return v; }
};

void log2(int n) {
    stack<Frame> s;
    while (n > 0) {
        s.push(Frame(n, n + 10));
        n--;
    }
    while (!s.empty()) {
        Frame frame = s.top();
        s.pop();
        cout << frame.getV() << endl;
    }
}

/*************************************************递归转非递归*******************************************************/
void log3(int n) {
    for (int i = 0; i < n; ++i) {
        int v = i + 10;
        cout << v << endl;
    }
}
