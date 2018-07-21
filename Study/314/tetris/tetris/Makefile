.PHONY: clean

OBJ = obj/def.o \
		obj/tetris.o\
		obj/keyboard.o\
		obj/main.o

CFLAGS= -Iinclude -g

all: tetris

tetris: $(OBJ)
	clang $(CFLAGS) $^ -o bin/$@ -std=gnu99

obj/%.o : src/%.c
	clang $(CFLAGS) -c $< -o $@ -std=gnu99

clean:
	rm -rf obj/*

