

.PHONY:clean

all:client server
server:poll_tcpServer.c
	clang $^ -o $@ -g 
client:client.c
	clang $^ -o $@ -g
clean:
	rm -f server client core.*
