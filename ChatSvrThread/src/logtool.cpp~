#include "../include/logtool.h"

char *itoa(char *str, int tmp)
{
    sprintf(str, "%d", tmp);
    return str;
}

void LOGD(const string str)
{
    time_t now = time(0);
    char *dt = ctime(&now);
    cout << "[DEBUG] ";
    cout << dt << " ";
    cout << str << endl;
}

void LOGE(const string str)
{
    time_t now = time(0);
    char *dt = ctime(&now);
    cout << "[ERROR] ";
    cout << dt << " ";
    cout << str << endl;
}
