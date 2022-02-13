#ifndef LOG_TOOL_H
#define LOG_TOOL_H

#include <string>
#include <iostream>
#include <ctime>

using namespace std;

char *itoa(char *str, int tmp);
void LOGD(const string str);
void LOGE(const string str);

#endif
