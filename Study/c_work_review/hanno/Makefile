.PHONY:clean hannuo
hano:hannuo.o main.o
	clang $^ -o $@ -lm

%.o:%.c
	clang -c $^ -o $@ -lm

clean:
	rm -rf *.o hannuo
