#include "../include/main.h"
#include <functional>

// 广播线程和主线程的通讯
int pipe_broadcast[2];
// 用户信息存储
map<int, UserInfo> userInfos;
// 连接socket和userInfos中的索引映射
map<int, int> sockfd_2_userIndex;
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
    pipe(pipe_broadcast);
    auto func_broadcast = []{
        doBroadCast(pipe_broadcast[0]);
        return;
    };
    Task<function<void()>> task_broadcast(func_broadcast);
    g_thread_pool.addTask(task_broadcast);

    // epoll监听监听socket
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
            int &event_fd = events[i].data.fd;
            int &userIndex = sockfd_2_userIndex[event_fd];
            if (event_fd == fd && events[i].events & EPOLLIN)
            {
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
                    if (userInfos[j].isInit())
                    {
                        index = j;
                        break;
                    }
                }
                if (index == -1)
                {
                    index = ++maxIndex;
                }

                sockfd_2_userIndex[new_fd] = index;
                userInfos[index].reset();
                socketpair(AF_UNIX, SOCK_STREAM, 0, userInfos[index].pipe);
                userInfos[index].socket = new_fd;
                ++user_cnt;

                auto func = [new_fd]{
                    doChildThread(new_fd);
                    return;
                };
                Task<function<void()>> task(func);
                g_thread_pool.addTask(task);
            }
            else if (event_fd == userInfos[userIndex].pipe[0] && events[i].events & EPOLLIN)
            {
                // 收到工作线程的消息
                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = recv(event_fd, buff, BUFF_SIZE, 0);

                send(pipe_broadcast[1], buff, ret_byte, 0);
            }
        }
        
    }


    close(fd);
    close(epoll_fd);

    return 0;
}

void doBroadCast(int read_fd)
{
    epoll_event events[MAX_EPOLL_CNT];
    int epoll_fd = epoll_create(MAX_EPOLL_CNT);
    addfd(epoll_fd, read_fd);

    while (1) {
        int num = epoll_wait(epoll_fd, events, MAX_EPOLL_CNT, -1);

        if (num <= 0)
        {
            break;
        }

        for (int i = 0; i < num; ++i) {
            if (events[i].data.fd == read_fd && events[i].events & EPOLLIN)
            {

                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = recv(read_fd, buff, BUFF_SIZE, 0);

                for (auto &elem : sockfd_2_userIndex) 
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

    while (1) {
        int num = epoll_wait(epoll_fd, events, MAX_EPOLL_CNT, -1);

        if (num <= 0)
        {
            break;
        }

        for (int i = 0; i < num; ++i) {
            if (events[i].data.fd == fd && events[i].events & EPOLLIN)
            {
                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = recv(fd, buff, BUFF_SIZE, 0);

                send(pipe_fd[1], buff, ret_byte, 0);
            }
            else if (events[i].data.fd == pipe_fd[1] && events[i].events & EPOLLIN)
            {
                char buff[BUFF_SIZE];
                memset(buff, '\0', BUFF_SIZE);
                int ret_byte = recv(pipe_fd[1], buff, BUFF_SIZE, 0);

                send(fd, buff, ret_byte, 0);
            }
        }
    }

    close(epoll_fd);
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
