CFLAGS=-g -Wall -pedantic

self-linker: self-linker.c
	gcc $(CFLAGS) -g -ldl -o self-linker self-linker.c

hello-world: hello-world.c
	gcc $(CFLAGS) -g -o hello-world hello-world.c

.PHONY: clean
clean:
	rm -f self-linker hello-world
