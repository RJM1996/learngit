.PHONY: clean

OBJ = obj/def.o \
		obj/tetris.o

CFLAGS= -Iinclude -g

all: tetris

tetris: $(OBJ)
	gcc $(CFLAGS) $^ -o bin/$@  -std=c99

obj/%.o : src/%.c
	gcc $(CFLAGS) -c $< -o $@ -std=c99

clean:
	rm -rf obj/*

