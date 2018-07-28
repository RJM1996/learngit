
.PHONY: build test clean

build: libmy_math.so

libmy_math.so: math.o
	g++ -shared -o $@ $^

math.o: math.cpp
	g++ -c -fPIC $^

test: d_main

d_main: test_math.cpp libmy_math.so
	g++ $^ -o $@ -L. -lmy_math
	LD_LIBRARY_PATH=. ./d_main

clean:
	rm -f *.o *.so d_main
