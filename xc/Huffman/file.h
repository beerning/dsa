//
//  test.h
//  ds
//
//  Created by berning on 2015/7/22.
//

#ifndef test_h
#define test_h

#include <map>
#include <fstream>
#ifdef _WIN64
#define FILE "F:/aberning/Documents/dev/c++/dsa/xc/Huffman/text1.txt"
//#define FILE "F:\\aberning\\Documents\\dev\\c++\\dsa\\xc\\Huffman\\text2.txt"
#else
#define FILE "/Users/aberning/Documents/dev/c++/dsa/xc/Huffman/text1.txt"
#endif

void testmap(){
        map<char, int> m;
        m.insert(pair<char, int>('a', 1));
        m.insert(pair<char, int>('z', 10));
        m.insert(pair<char, int>('f', 3));
        m.insert(pair<char, int>('p', 111));
    
    //    cout << m.size() << endl;
    //
    //    cout << m.at('p') << endl;
        map<char,int>::iterator it;
        for (it = m.begin(); it != m.end(); ++it)
            cout << it->first << " => " << it->second << '\n';
    
        for (char s = 'A'; s <= 'z'; s++){
            it = m.find(s);
            if (it != m.end())
                cout << s << " : true" << endl;
            else
                cout << s << " : false" << endl;
        }
}

void testmap1(const char* _s){
    map<char, int> m;
    unsigned long len = strlen(_s);
    cout << len << endl;
    
    for (int i = 0; i < len; i++){
        char c = _s[i];
        
        int v = 1;
        if (m[c] != 0)
            v = m[c] + 1;
        m[c] = v;
    }
    
    map<char,int>::iterator it;
    for (it = m.begin(); it != m.end(); ++it)
        cout << it->first << " => " << it->second << '\n';
}

//fin和cin一样会将所有的空格当做终止条件，这样就没有办法输出空格信息了
void testFile1(){
    ifstream fin;
    fin.open(FILE);
    if (!fin.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }
    
    char buff[1024] = {0};
//    fin >> buff遇到EOF（end of file）会返回false
    string ss;  //ABBBCCCCCCCCDDDDDDEEFFGGG 无空格
    while (fin >> buff) {
        ss += buff;
        cout << buff << endl;
    }
  
    cout << "ss :" << ss << endl;

    fin.close();
}

void testFile2(){
    ifstream fin;
    fin.open(FILE);
    if (!fin.is_open()) {
        cout << "failed" << endl;
        return;
    }
    
    string buff;
    string str;
    while (getline(fin, buff)){
        cout << buff << endl;
        str += buff += "\n";
    }
    fin.close();
    
    cout << "str: " << endl;
    cout << str << endl;

}

void testFile3(){
    ifstream fin;
    fin.open(FILE);
    if (!fin.is_open()) {
        cout << "failed" << endl;
        return;
    }

    char buff[1024] = {0};
    while (fin.getline(buff, sizeof(buff))){
        cout << buff << endl;
    }
    fin.close();
    cout << buff << endl;

}
void testFile4(){
    ifstream fin;
    fin.open(FILE);
    if (!fin.is_open()) {
        cout << "failed" << endl;
        return;
    }
    
    char buff = 0;
    string ss;
    int i = 0;
    while ((buff = fin.get()) != EOF){
        //ss.push_back(buff);
        ss += buff;
        i++;
        cout << buff;
    }
    cout << endl << "ss :" << endl;
    cout << ss << endl; // \377 ？

    fin.close();
}


#endif /* test_h */
