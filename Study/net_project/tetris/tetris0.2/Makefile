.PHONY: clean

OBJ = obj/def.o \
		obj/tetris.o \
		obj/keyboard.o \
		obj/main.o

CFLAGS= -Iinclude -g

all:main 

main: $(OBJ)
	gcc $(CFLAGS) $^ -o bin/$@ -std=c99

obj/%.o : src/%.c
	gcc $(CFLAGS) -c $< -o $@ -std=c99

clean:
	rm -rf obj/*

