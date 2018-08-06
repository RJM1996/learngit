ROOT=$(shell pwd)
INCLUDE=-I/usr/include/mysql
LIB=-L/usr/lib64/mysql
LIB_NAME=-lmysqlclient -lpthread
LD_FLAG=#-static

.PHONY:all
all:netCal insertData selectData

netCal:netCal.c
	gcc -o $@ $^
insertData:insertData.c
	gcc -o $@ $^ $(INCLUDE) $(LIB) $(LIB_NAME) $(LD_FLAG)
selectData:selectData.c
	gcc -o $@ $^ $(INCLUDE) $(LIB) $(LIB_NAME) $(LD_FLAG)

.PHONY:clean
clean:
	rm -f netCal insertData selectData
