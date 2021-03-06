#ifndef MAIN_H
#define MAIN_H

#include <functional>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <map>

#include "threadpool.h"
#include "tool.h"

#define CHAT_CNT 1
#define REST_RECV_CNT 10
#define BUFF_SIZE 100
#define CONNECT_INTERVAL 1
#define MAX_EPOLL_CNT 5

using namespace std;

typedef function<void()> lambdaType;

void doNewConnect(sockaddr_in addr);

void doChatLogic(int fd);

#endif

