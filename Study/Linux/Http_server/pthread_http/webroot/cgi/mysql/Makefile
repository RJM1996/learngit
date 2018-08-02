
.PHONY:clean
select:select.c
	gcc $^ -o $@ -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient

clean:
	rm -rf select

