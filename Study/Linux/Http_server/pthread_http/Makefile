ROOT=$(shell pwd)

.PHONY:clean

.PHONY:all

all:main cgi

main:httpServer.c url.c
	gcc $^ -o $@ -g -lpthread
cgi:
	cd $(ROOT)/webroot/cgi/mysql; make clean; make; cd -
	cd $(ROOT)/webroot/cgi/cal; make clean; make; cd -
	cd $(ROOT)/webroot/cgi/date; make clean; make; cd -

clean:
	rm -f main core.*
