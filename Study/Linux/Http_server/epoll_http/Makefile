.PHONY:clean

server:main.cpp epoll_http.cpp
	g++ -o $@ $^ -g 

clean:
	rm -f server core.*
