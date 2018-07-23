

.PHONY:clean
server:http_server.c
	clang $^ -o $@ -g -std=c99
clean:
	rm -f server core.*
