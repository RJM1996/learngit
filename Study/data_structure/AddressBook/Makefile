.PHONY:clean
main:main.o addressbook.o
	gcc $^ -o $@ -g -std=c99
%.o:%.c
	gcc -c $^ -o $@ -g -std=c99
clean:
	rm -rf *.o core.* 
