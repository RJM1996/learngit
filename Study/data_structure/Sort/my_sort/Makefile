.PHONY:all

all:sort select

sort:sort.c
	clang $^ -o $@ -std=c99 -g
select:select.c
	clang $^ -o $@ -std=c99 -g

clean:
	rm -f sort select

