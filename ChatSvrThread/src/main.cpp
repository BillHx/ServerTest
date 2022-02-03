#include "../include/main.h"
#include "../include/threadpool.h"
#include <cassert>
#include <netinet/in.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

bool stop_server = false;
ThreadPool g_thread_pool;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        LOGE("param error");
        return 0;
    }

    char *ip = argv[1];
    int port = htons(atoi(argv[2])); 

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    inet_pton(AF_INET, ip, &(addr.sin_addr));

    int ret = bind(fd,  (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        LOGE("bind socket error");
        return 0;
    }

    ret = listen(fd, 5);
    if (ret == -1)
    {
        LOGE("listen socket error");
        return 0;
    }

    int epoll_fd = epoll_create(MAX_EPOLL_CNT);
    addfd(epoll_fd, fd);

    while (!stop_server) {
        epoll_event events[MAX_EPOLL_CNT];
        int ret_epoll = epoll_wait(epoll_fd, events, MAX_EPOLL_CNT, -1);
        if (ret_epoll <= 0)
        {
            LOGE("epoll_wait error");
            break;
        }

        for (int i = 0; i < ret_epoll; ++i) {
            if (events[i].data.fd == fd && events[i].events & EPOLLIN)
            {
                // 收到connect请求
                // 这里因为不需要用到客户端信息，所以直接用sockaddr类型
                struct sockaddr addr_client;
                socklen_t sz_client;
                bzero(&addr_client, sizeof(addr_client));
                int new_fd = accept(fd, &addr_client, &sz_client);

            }
        }
        
    }


    close(fd);
    close(epoll_fd);

    return 0;
}

int addfd(int epoll_fd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    return 0;
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
