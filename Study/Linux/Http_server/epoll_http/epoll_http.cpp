
// ET 模式的epoll
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include "epoll_http.h"

using namespace std;

#define MAX 20
#define MAX_SIZE 1024

// setNoBlock
// 将一个文件描述符设置为非阻塞
void setNoBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL);
    if(fl < 0)
    {
        perror("fcntl");
        return ;
    }
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

//////////////////////////////////
// 实现相应接口
//////////////////////////////////

// 1, 获取监听套接字
int startUp(int port)
{
    if(port < 1024)
    {
        printf("Usage: ./server [port > 1024]\n");
        return 2;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listen_fd < 0)
    {
        perror("socket");
        return 3;
    }
    // 绑定
    // int bind(int sockfd, const struct sockaddr *addr,
    //          socklen_t addrlen);
    int bind_ret = bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(bind_ret < 0)
    {
        perror("bind");
        return 4;
    }
    // 监听
    int listen_ret = listen(listen_fd, 5);
    if(listen_ret < 0)
    {
        perror("listen");
        return 5;
    }
    return listen_fd;
}

// 2, 监听套接字就绪, 开始获取连接
void getConnect(int listen_fd, int epoll_fd)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    // 连接
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int connect_fd = accept(listen_fd, (struct sockaddr*)&client, &len);
    if(connect_fd < 0)
    {
        perror("accept");
        return ;
    }
    // 到这里连接成功
    printf("get a new client: [%s | %d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    // 将其设置为非阻塞
    setNoBlock(connect_fd);
    // 将这个新获取的套接字添加到epoll_fd中
    struct epoll_event ev;
    ev.data.fd = connect_fd;
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &ev);
    if(ret < 0)
    {
        perror("epoll_ctl");
        return ;
    }
}

// 实现无阻塞地读的接口
ssize_t noBlockRead(int fd, char* buf, int size)
{
    (void) size;
    ssize_t total_size = 0;
    while(1)
    {
        ssize_t cur_size = read(fd, buf + total_size, sizeof(buf)/sizeof(buf[0]));
        total_size += cur_size;
        if(cur_size < (ssize_t)(sizeof(buf)/sizeof(buf[0])) || errno == EAGAIN)
        {
            break;
        }
    }
    buf[total_size] = 0;
    return total_size;
}

// 获取报头的每一行
// 要把 \r -> \n || \r\n -> \n
int get_line(int sock, char line[], int size)
{
    int i = 0;
    char ch = 'a';
    while(i < size - 1 && ch != '\n')
    {
        // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
        ssize_t size = recv(sock, &ch, 1, 0); // 一次读一个字符
        if(size <= 0)
        {
            // 出错或者连接中断
            return -1;
        }
        else
        {
            // 继续判断
            if(ch == '\r')
            {
                // 窥探下一个字符
                // MSG_PEEK 窥看外来消息, 只看一下, 不读走
                size = recv(sock, &ch, 1, MSG_PEEK);
                if(size <= 0)
                {
                    return -1;
                }
                else
                {
                    if(ch == '\n')
                    {
                        // 如果接下来的一个字符是 '\n'
                        // 那么就把它读上来
                        size = recv(sock, &ch, 1, 0);
                        if(size <= 0)
                        {
                            return -1;
                        }
                    }
                    else
                    {
                        // 如果不是说明这一行已经完了, 把'\r'变为'\n'
                        ch = '\n';
                    }
                }
            }
            line[i++] = ch;
        }
    }
    line[i] = '\0';
    return i;
}

// 响应, 传回网页
int echo_www(int sock, const char* resource_path, int size)
{
    int fd = open(resource_path, O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return 404;
    }

    // 状态行
    // 空行
    // status_line, blank_line;
    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    send(sock, status_line, strlen(status_line), 0);

    char len_buf[MAX_SIZE/4] = {0};
    // content_length = "Content-Length: %u\r\n"
    sprintf(len_buf, "Content-Length: %u\r\n", size);
    send(sock, len_buf, strlen(len_buf), 0);

    send(sock, blank_line, strlen(blank_line), 0);

    // ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    // 在内核中, 两个文件描述符之间直接进行读写, 效率高
    ssize_t ret = sendfile(sock, fd, NULL, size);
    if(ret < 0)
    {
        perror("sendfile");
        return 404;
    }
    close(fd);
    return 200;
}


void echo_error(int sock, int status_code)
{
    string _404_path = "webroot/error_code/404/404.html";
    int fd = open(_404_path.c_str(), O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return ;
    }

    char buf[MAX_SIZE/4];
    sprintf(buf, "HTTP 404 Not Found");
    send(sock, buf, strlen(buf), 0);

    send(sock, blank_line, strlen(blank_line), 0);

    // ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    // 在内核中, 两个文件描述符之间直接进行读写, 效率高
    struct stat st;
    stat(_404_path.c_str(), &st);
    ssize_t ret = sendfile(sock, fd, NULL, st.st_size);
    if(ret < 0)
    {
        perror("sendfile");
        return ;
    }
    close(fd);
}


void handle_hander(int sock)
{
    char buf[1024];
    int ret = -1;
    do
    {
        ret = get_line(sock, buf, sizeof(buf));
    } while(ret > 0 && strcmp(buf, "\n") != 0);
}

// 返回状态信息
void status_response(int sock, int status_code)
{
    handle_hander(sock);
    switch(status_code)
    {
        case 404:
            echo_error(sock, status_code);
            break;
        case 503:

        default: ;
    }
}


// 2, 正常客户端就绪, 开始服务
void service(int client, int epoll_fd)
{
    char line[1024] = {0};
    int status_code;

    // 现在 client 里面存的就是浏览器的请求信息
    // 一行一行地提取浏览器的请求存到 buf 里面
    int ch_size = get_line(client, line, sizeof(line));
    cout << "ch_size: " << ch_size << endl;
    line[ch_size] = '\0';
    printf("请求行: %s", line);

    // 首先提取出请求方法
    size_t i = 0;
    size_t j = 0;
    char method[MAX_SIZE/4];
    while(i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j]))
    {
        method[i++] = line[j++];
    }
    method[i] = '\0';
    cout << "请求方法 : " << method << endl;
    // 到这里就已经提取到了请求方法
    // 为了避免请求方法之后不止一个空格, 需要把后面的空格都跳过
    while(j < sizeof(line) && isspace(line[j]))
    {
        j++;
    }
    // 此时 j 指向了 URL
    char url[MAX_SIZE];
    i = 0;
    while(i < sizeof(url)-1 && j < sizeof(line) && !isspace(line[j]))
    {
        url[i] = line[j];
        i++, j++;
    }
    url[i] = '\0';
    cout << "请求资源路径 : " << url << endl;
    // 到这里 url 也提取到了
    // 版本号暂时忽略不提取, 默认 HTTP/1.0
    // 接下来判断请求方法, 因为本服务器仅支持 get 和 post
    // int strcasecmp(const char *s1, const char *s2); 忽略大小写的字符串比较
    if(strcasecmp(method, "GET") != 0 && strcasecmp(method, "POST") != 0)
    {
        status_code = 404;
        // 如果请求方法不是 get || post, 就返回错误码, 关闭连接.
        printf("请求方法不是 GET 和 POST !\n");
        // 关闭打开的文件
    }
    // 到这里肯定是 GET 或 POST
    // CGI: 
    //     1, GET方法 带参数 是CGI, 参数在地址栏
    //     2, POST方法都是CGI, 参数在消息正文, 敏感信息的参数传递都用POST方法
    int cgi_flag = 0;
    char* query_string = NULL;
    if(strcasecmp(method, "POST") == 0)
    {
        cgi_flag = 1;
    }
    else
    {
        // GET 方法
        query_string = url;
        while(*query_string != '\0')
        {
            // https://www.baidu.com/s?ie=utf-8wd=花
            // 我们发现GET方法的URL中只要有问号, 说明就是带参数的, ? 后面的就是参数
            if(*query_string == '?')
            {
                // 把问号前后分离
                *query_string = '\0';
                query_string++;
                cgi_flag = 1;
                break;
            }
            query_string++; // 遍历url
        }
    }
    char resource_path[MAX_SIZE];
    sprintf(resource_path, "webroot%s", url);
    if(resource_path[strlen(resource_path)-1] == '/')
    {
        strcat(resource_path, "index.html");
    }
    cout << "请求资源路径 : " << resource_path << endl;

    // int stat(const char *file_name, struct stat *buf);
    // 通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
    // 执行成功则返回0，失败返回-1，错误代码存于errno
    struct stat st;
    if(stat(resource_path, &st) < 0)
    {
        status_code = 404;
        // 文件不存在
        printf("文件不存在 !\n");
        // 关闭打开的文件
    }
    else
    {
        if(S_ISDIR(st.st_mode)) // 如果请求资源是一个目录
        {
            strcat(resource_path, "index.html"); // 把目录的首页拼接到资源路径中
        }
        // 如果请求的资源具有可执行权限
        else if(
                (st.st_mode & S_IXUSR) ||
                (st.st_mode & S_IXGRP) ||
                (st.st_mode & S_IXOTH)
               )
        {
            cgi_flag = 1;
        }
        else
        {
            // TODO
        }

        if(cgi_flag == 1)
        {
            // status_code = exe_cgi(client, method, resource_path, query_string);
        }
        else
        {

            int ret = noBlockRead(client, line, sizeof(line)-1);
            if(ret < 0)
            {
                status_code = 404;
                perror("read");
            }
            if(ret == 0)
            {
                printf("client quit !\n");
                close(client);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client, NULL);
                return ;
            }

            line[ret] = 0;
            printf("\n=====================================\n");
            printf("client say :\n%s\n", line);
            printf("\n=====================================\n");

            status_code = echo_www(client, resource_path, st.st_size);
        }
    }

    /*
    const std::string home = "./webroot/index.html";
    if(stat(home.c_str(), &st) < 0)
    {
        printf("文件不存在\n");
        perror("stst");
        return ;
    }
    int index_fd = open(home.c_str(), O_RDONLY);

    // 定义状态行和空行
    const char* status_line = "HTTP/1.0 200 OK\r\n";                                                                   
    const char* blank_line = "\r\n";
    // 1.发送响应状态行
    send(client, status_line, strlen(status_line), 0);

    // 2.发送Content-Length用于描述HTTP消息实体的传输长度
    char len_buf[256] = {0};
    // content_length = "Content-Length: %u\r\n"
    sprintf(len_buf, "Content-Length: %lu\r\n", st.st_size);
    send(client, len_buf, strlen(len_buf), 0);

    // 3.发送空行
    send(client, blank_line, strlen(blank_line), 0);

    // 4.发送所请求的资源
    // ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    if(sendfile(client, index_fd, NULL, st.st_size) < 0)
    {
        perror("sendfile");
    }
    */

    cout << "状态码 : " << status_code << endl;
    if(status_code != 200)
    {
        status_response(client, status_code);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./server [port > 1024]\n");
        return 1;
    }

    // 首先要获取监听套接字
    int listen_sock = startUp(atoi(argv[1]));

    // 创建 epoll 模型
    int epfd = epoll_create(MAX);

    // 将 listen_sock 设置为非阻塞
    setNoBlock(listen_sock);

    // 将监听套接字注册到 epoll 模型中
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listen_sock;
    int epoll_ctl_ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);
    if(epoll_ctl_ret < 0)
    {
        perror("epoll_ctl");
        return 6;
    }

    // 循环等待连接, 提供服务
    while(1)
    {
        struct epoll_event evs[MAX];
        // 获取就绪事件
        int epoll_wait_ret = epoll_wait(epfd, evs, MAX, -1);
        if(epoll_wait_ret < 0)
        {
            perror("epoll_wait");
            continue;
        }
        if(epoll_wait_ret == 0)
        {
            printf("epoll timeout !\n");
            continue;
        }
        // 到这里说明有事件就绪了
        for(int i = 0; i < epoll_wait_ret; i++)
        {
            // 如果不是读事件就绪
            if(!(evs[i].events & EPOLLIN))
            {
                continue;
            }
            // 如果是监听套接字的读事件就绪
            if(evs[i].data.fd == listen_sock)
            {
                // 开始进行连接
                getConnect(listen_sock, epfd);
            }
            else
            {
                // 说明是正常客户端的读事件就绪, 开始服务
                service(evs[i].data.fd, epfd);
            }
        } // loop 1 end
    } // loop 2 end
    return 0;
}
