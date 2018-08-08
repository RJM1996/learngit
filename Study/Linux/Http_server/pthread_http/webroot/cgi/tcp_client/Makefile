
.PHONY:clean

all:server client

server:server.cpp
	clang++ $^ -o $@ -g -lpthread

client:client.c
	clang -o $@  $^ -g 

clean:
	rm -f client server
