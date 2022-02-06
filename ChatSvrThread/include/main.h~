#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <cassert>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include "threadpool.h"

#define MAX_CONN_CNT 100
#define MAX_EPOLL_CNT 5

typedef int (*TaskFunc)(int, char *);

using namespace std;

int addfd(int epoll_fd, int fd);

int doRead();

void LOGD(const string str);
void LOGE(const string str);

#endif
