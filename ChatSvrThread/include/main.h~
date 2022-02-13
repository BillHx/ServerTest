#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <cassert>
#include <functional>
#include <map>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "threadpool.h"

#define MAX_CONN_CNT 100
#define MAX_EPOLL_CNT 5

#define BUFF_SIZE 20

using namespace std;

typedef function<void()> lambdaType;

// 用户信息存储
struct UserInfo
{
    int pipe[2];
    int socket;

    UserInfo()
    {
        reset();
    }

    void reset()
    {
        pipe[0] = -1;
        pipe[1] = -1;
        socket = -1;
    }

    bool isInit()
    {
        return socket == -1;
    }
};

int addfd(int epoll_fd, int fd);
int delfd(int epoll_fd, int fd);

void sig_handler(int sig);
int addsig(int sig);

int doRead(int fd);
int doSendAll(int read_fd);

void doBroadCast(int read_fd);
void doChildThread(int fd, int pipe_fd[]);

#endif
