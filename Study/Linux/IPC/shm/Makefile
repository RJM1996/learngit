.PHONY:all
all:server client 

server:server.c comm.c
	gcc $^ -o $@ -g
client:client.c comm.c
	gcc $^ -o $@ -g
	

clean:
	rm -f server client


