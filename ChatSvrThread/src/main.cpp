#include "../include/main.h"
#include "../include/logtool.h"
#include <csignal>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

// 广播线程和主线程的通讯
int pipe_broadcast[2];
// 用户信息存储
map<int, UserInfo> userInfos;
// 信号处理管道
int pipe_sig[2];
// 主线程监听的管道fd和userInfos中的索引映射
map<int, int> pipefd_2_userIndex;
int maxIndex = 0;
int user_cnt = 0;

bool stop_server = false;
ThreadPool<lambdaType> g_thread_pool;

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

    // 广播线程生成
    // socketpair(AF_UNIX, SOCK_STREAM, 0, pipe_broadcast);
    pipe(pipe_broadcast);
    auto func_broadcast = []{
        doBroadCast(pipe_broadcast[0]);
        return;
    };
    Task<lambdaType> task_broadcast(func_broadcast);
    g_thread_pool.addTask(task_broadcast);

    // epoll监听监听socket
    int epoll_fd = epoll_create(MAX_EPOLL_CNT);
    addfd(epoll_fd, fd);

    // 信号监听
    pipe(pipe_sig);
    addfd(epoll_fd, pipe_sig[0]);

    while (!stop_server) {
        epoll_event events[MAX_EPOLL_CNT];
        int ret_epoll = epoll_wait(epoll_fd, events, MAX_EPOLL_CNT, -1);
        if (ret_epoll <= 0)
        {
            if (errno != EINTR) 
            {
                LOGE("epoll_wait error");
                break;
            }
        }

        for (int i = 0; i < ret_epoll; ++i) {
            int event_fd = events[i].data.fd;
            if (event_fd == fd && events[i].events & EPOLLIN)
            {
                LOGD("accept socket");
                // 收到connect请求
                // 这里因为不需要用到客户端信息，所以直接用sockaddr类型
                struct sockaddr addr_client;
                socklen_t sz_client;
                bzero(&addr_client, sizeof(addr_client));
                int new_fd = accept(fd, &addr_client, &sz_client);

                // 增加连接socket监听
                // 搜寻可用索引
                int index = -1;
                for (int j = 0; j <= maxIndex; ++j) {
                    if (userInfos.find(j) == userInfos.end())
                    {
                        index = j;
                        break;
                    }
                }
                if (index == -1)
                {
                    index = ++maxIndex;
                }

                socketpair(AF_UNIX, SOCK_STREAM, 0, userInfos[index].pipe);
                userInfos[index].socket = new_fd;
                addfd(epoll_fd, userInfos[index].pipe[0]);
                pipefd_2_userIndex[userInfos[index].pipe[0]] = index;
                ++user_cnt;

                auto func = [new_fd, index]{
                    doChildThread(new_fd, userInfos[index].pipe);
                    return;
                };
                Task<lambdaType> task(func);
                g_thread_pool.addTask(task);
            }
            else if (event_fd == pipe_sig[0] && events[i].events & EPOLLIN) 
            {
                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = read(pipe_sig[0], buff, BUFF_SIZE);

                for (int j = 0; j < ret_byte; ++j) {
                    switch (buff[j]) 
                    {
                        case SIGTERM:
                        {
                            stop_server = true;
                            break;
                        }
                        default:
                            break;
                    }
                }
                
            }
            else
            {
                // 广播消息
                map<int, int>::iterator iter = pipefd_2_userIndex.find(event_fd);
                if (iter != pipefd_2_userIndex.end())
                {
                    if (event_fd == userInfos[iter->second].pipe[0] && events[i].events & EPOLLIN)
                    {
                        LOGD("send pipe, ready to broadcast");
                        // 收到工作线程的消息
                        char buff[BUFF_SIZE];
                        memset(buff, '\0', BUFF_SIZE);
                        int ret_byte = recv(event_fd, buff, BUFF_SIZE, 0);

                        write(pipe_broadcast[1], buff, ret_byte);
                    }
                }
            }
        }
        
    }


    close(fd);
    close(epoll_fd);
    close(pipe_broadcast[1]);
    close(pipe_broadcast[0]);
    close(pipe_sig[0]);
    close(pipe_sig[1]);

    return 0;
}

void doBroadCast(int read_fd)
{
    epoll_event events[MAX_EPOLL_CNT];
    int epoll_fd = epoll_create(MAX_EPOLL_CNT);
    addfd(epoll_fd, read_fd);

    while (!stop_server) {
        int num = epoll_wait(epoll_fd, events, MAX_EPOLL_CNT, -1);

        if (num <= 0)
        {
            if (errno != EINTR) 
            {
                break;
            }
        }

        for (int i = 0; i < num; ++i) {
            if (events[i].data.fd == read_fd && events[i].events & EPOLLIN)
            {
                LOGD("broadcast thread: send pipe");

                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = read(read_fd, buff, BUFF_SIZE);

                for (auto &elem : pipefd_2_userIndex) 
                {
                    UserInfo &info = userInfos[elem.second];
                    // tee(read_fd, info.pipe[0], , unsigned int __flags);
                    send(info.pipe[0], buff, ret_byte, 0);
                }

            }
        }
    }

    close(epoll_fd);
}

void doChildThread(int fd, int pipe_fd[])
{
    // 子线程直接负责本fd的数据处理
    epoll_event events[MAX_EPOLL_CNT];
    int epoll_fd = epoll_create(MAX_EPOLL_CNT);

    addfd(epoll_fd, fd);
    addfd(epoll_fd, pipe_fd[1]);

    bool stop_thread = false;
    while (!stop_thread) {
        int num = epoll_wait(epoll_fd, events, MAX_EPOLL_CNT, -1);

        if (num <= 0)
        {
            if (errno != EINTR) 
            {
                break;
            }
        }

        for (int i = 0; i < num; ++i) {
            if (events[i].data.fd == fd && events[i].events & EPOLLIN)
            {
                LOGD("child thread: recv socket");
                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = recv(fd, buff, BUFF_SIZE, 0);

                if (ret_byte == 0)
                {
                    // 断开连接
                    stop_thread = true;
                    break;
                }

                send(pipe_fd[1], buff, ret_byte, 0);
            }
            else if (events[i].data.fd == pipe_fd[1] && events[i].events & EPOLLIN)
            {
                LOGD("child thread: send socket");
                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = recv(pipe_fd[1], buff, BUFF_SIZE, 0);

                send(fd, buff, ret_byte, 0);
            }
        }
    }

    close(epoll_fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // 清空数据
    int key1 = -1;
    int key2 = -1;
    for (auto &elem : userInfos) {
        if (elem.second.socket == fd)
        {
            key1 = elem.second.pipe[0];
            key2 = elem.first;
        }
    }

    if (key1 != -1)
    {
        pipefd_2_userIndex.erase(key1);
        userInfos.erase(key2);
    }
}

int addfd(int epoll_fd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    return 0;
}

int delfd(int epoll_fd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event);
    return 0;
}

void sig_handler(int sig)
{
    // 按字节发送
    int msg = sig;
    write(pipe_sig[1], (char *)&msg, 1);
    return ;
}

int addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    sigaction(sig, &sa, NULL);
    return 0;
}

