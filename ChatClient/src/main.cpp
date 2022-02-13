#include<iostream>
#include<sys/socket.h>
#include<cstdlib>
#include<arpa/inet.h>
#include<cstring>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<cstdio>
#include <sys/select.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

#define BUFF_SIZE 10

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "please input my ip and port" << endl;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in serAddr;
    bzero(&serAddr, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(serAddr.sin_addr));
    serAddr.sin_port = htons(port);

    // 创建socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd != -1)
    {
        cout << "hx create socket success sockfd = " << fd << endl;
    }
    else
    {
        cout << "create socket fail" << endl;
        return 0;
    }

    // 发起连接socket
    int res = connect(fd, (struct sockaddr*)&serAddr, sizeof(serAddr));
    if (res == 0)
    {
        cout << "connect socket success sockfd = " << fd << endl;
    }
    else
    {
        cout << "connect socket fail" << fd << endl;
        cout << "error msg:" << strerror(errno) << endl;
        return 0;
    }


    int pipe_fd[2];
    pipe(pipe_fd);
    fd_set read_set;
    fd_set write_set;
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);

    while (1) 
    {
        FD_SET(0, &read_set);
        FD_SET(fd, &read_set);
        int ret = select(fd + 1, &read_set, NULL, NULL, NULL);

        if (ret < 0)
        {
            cout << "select error ..." << endl;
            continue;
        }

        // 需要判断服务关闭的情况，要不然会一直循环收到fd可读
        cout << "something happen ..." << endl;
        if (FD_ISSET(fd, &read_set))
        {
            cout << "socket fd change" << endl;
            // 收到socket消息
            char buff[BUFF_SIZE];
            memset(buff, '\0', BUFF_SIZE);
            int ret_byte = recv(fd, buff, BUFF_SIZE - 1, 0);
            if (ret_byte > 0)
            {
                cout << "recv msg :" << string(buff) << endl;
            }
            else
            {
                cout << "recv msg empty" << endl;
                break;
            }
        }
        else if (FD_ISSET(0, &read_set))
        {
            cout << "do stander input" << endl;
            // 收到标准输入
            // splice参数必须有一个管道文件描述符
            splice(0, NULL, pipe_fd[1], NULL, 32768, SPLICE_F_MORE);
            splice(pipe_fd[0], NULL, fd, NULL, 32768, SPLICE_F_MORE);
        }
        
    }

    close(fd);
    return 0;
}
