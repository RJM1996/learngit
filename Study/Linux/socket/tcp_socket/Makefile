.PHONY:all
all:server client
	
client:tcp_client.c
	clang $^ -o $@ -g -lpthread
server:tcp_server.c
	clang $^ -o $@ -g -lpthread

clean:
	rm -rf server client
