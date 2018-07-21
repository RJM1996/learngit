.PHONY:all

all:client server

client:udp_client.c
	clang $^ -o $@ -g -std=c99
server:udp_server.c
	clang $^ -o $@ -g -std=c99

clean:
	rm -rf client server
