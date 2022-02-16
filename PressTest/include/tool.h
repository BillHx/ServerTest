#ifndef TOOL_H
#define TOOL_H

#include <string>
#include <cstring>
#include <iostream>
#include <ctime>

#include <sys/epoll.h>
#include <signal.h>
#include <fcntl.h>

using namespace std;

char *itoa(char *str, int tmp);
void LOGD(const string str);
void LOGE(const string str);

void addEpollFD(int epoll_fd, int fd, bool isET);
void delEpollFD(int epoll_fd, int fd);

void addSig(int sig, void *sig_handler(int));

int setNoBlocking(int fd);

#endif
