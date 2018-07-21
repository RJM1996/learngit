.PHONY:all
all:dst src

dst:dst_fifo.c
	gcc $^ -o $@
src:src_fifo.c
	gcc $^ -o $@

clean:
	rm -f dst src

