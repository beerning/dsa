#pragma once

#include <time.h>
#include <Windows.h>

void test() {


	//time_t stamp = time(NULL);

	//struct tm tm;
	//gmtime_s(&tm, &stamp);
	////localtime_s(&tm, &stamp);
	//time_t stamp2 = mktime(&tm);

	//SYSTEMTIME systime;
	//GetLocalTime(&systime);

	const char* a = "abc";
	const char* b = "def";
	////char c[7];
	char* c = (char*)malloc(sizeof(char*));

	memset(c, 0, sizeof(char *));
	strcpy_s(c, sizeof(c), a);
	strcat_s(c, sizeof(c), b);

	//char stringBuffer[80];
	//memset(stringBuffer, 0, 80);
	/*strcpy_s(stringBuffer, _countof(stringBuffer), "Hello world from ");
	strcat_s(stringBuffer, _countof(stringBuffer), "strcpy_s ");
	strcat_s(stringBuffer, _countof(stringBuffer), "and ");
	strcat_s(stringBuffer, _countof(stringBuffer), "strcat_s!");*/
}


//获取时间戳 time(time_t *stamp) mktime(struct tm *tm)
//获取时间字符串 ctime(time_t *stamp) asctime(struct tm *tm) strftime(char *s, int max_char, const char *format, struct tm *tm)
//获取时间类 localtime(const time_t *stamp)  gmtime(cosnt time_t *stamp)
//时间差 difftime(time_t end, time_t begin)