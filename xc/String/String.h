#pragma once

#define NOTFOUND -1

int indexOf1(string text, string pattern) {
	size_t tlen = text.size();
	size_t plen = pattern.size();
	if (tlen == 0 || plen == 0 || tlen < plen) return NOTFOUND;

	int ti = 0, pi = 0;
	int smax = tlen - plen; //max start index
	while (pi < plen && ti - pi <= smax) {
		if (text[ti] != pattern[pi]) {
			ti -= pi - 1;
			pi = 0;
		}
		else {
			ti++;
			pi++;
		}
	}
	return  pi == plen ? ti - pi : NOTFOUND;
}

int indexOf2(string text, string pattern) {
	size_t tlen = text.size();
	size_t plen = pattern.size();
	if (tlen == 0 || plen == 0 || tlen < plen) return NOTFOUND;

	int smax = tlen - plen; //max start index  
	for (int ti = 0; ti <= smax; ++ti) {
		int pi = 0;
		for ( ; pi < plen; ++pi) 
			if (text[ti + pi] != pattern[pi]) break;
		if (pi == plen) return ti;
	}
	return NOTFOUND;
}

//next
void getNext(int *next, string pattern) {
	int i = 0;	//i point to the end of suffix
	int j = next[i] = -1; //j point to the end of prefix
	int emax = pattern.size() - 1; //max end index
	while (i < emax) {
		if (j < 0 || pattern[i] == pattern[j]) {
			//next[++i] = ++j; //"AAAB",exists unnecessary comparison
			next[++i] = pattern[i] == pattern[++j] ? next[j] : j; //optimization
		}
		else {
			j = next[j];
		}
	}
}

//KMP
int indexOf(string text, string pattern) {
	int tlen = (int)text.size();
	int plen = (int)pattern.size();
	if (tlen == 0 || plen == 0 || tlen < plen) return NOTFOUND;

	int* next = new int[plen] {};
	getNext(next, pattern);
	
	int ti = 0, pi = 0;
	int smax = tlen - plen; //max start index
	while (pi < plen && ti - pi <= smax) {
		if (pi >= 0 && pattern[pi] != text[ti]) {
			pi = next[pi];
		}
		else {
			ti++;
			pi++;
		}	
	}
	delete[] next;
	return pi == plen ? ti - pi : NOTFOUND;
}


void test() {
	string text = "adcadadbadac";
	string pattern = "bad";
	
	cout << indexOf(text, pattern) << endl;
}