#include "../include/tool.h"
#include <csignal>
#include <cstring>
#include <fcntl.h>
#include <sys/epoll.h>

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

void addEpollFD(int epoll_fd, int fd, bool isET)
{
    epoll_event event;
    event.events = EPOLLIN;
    if (isET)
    {
        event.events |= EPOLLET;
    }
    event.data.fd = fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
}

void delEpollFD(int epoll_fd, int fd)
{
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
}

void addSig(int sig, void sig_handler(int))
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_flags |= SA_RESTART;
    sa.sa_handler = sig_handler;
    sigfillset(&sa.sa_mask);
    sigaction(sig, &sa, NULL);
}

int setNoBlocking(int fd)
{
    int old_opt = fcntl(fd, F_GETFL);
    int new_opt = old_opt | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_opt);
    return old_opt;
}

