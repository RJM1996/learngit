.PHONY:clean
cp:cp.o
	gcc $^ -o $@ 
%.o:%.c
	gcc -c $^ -o $@
clean:
	rm -rf *.o
