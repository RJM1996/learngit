.PHONY:clean
server:epoll_tcpServer.c
	clang $^ -o $@ -g -std=c99
clean:
	rm -f server core.*
