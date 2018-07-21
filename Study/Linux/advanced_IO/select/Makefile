

.PHONY:clean
server:select_tcpServer.c
	clang $^ -o $@ -g -std=c99
clean:
	rm -f server core.*
