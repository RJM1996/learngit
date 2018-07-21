.PHONY:clean jdt
jdt:test.c
	gcc $^ -o $@
%.o:%.c
	gcc -c $^ -o $@
clean:
	rm -rf *.o jdt
