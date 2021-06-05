all: test

test:  main.c
	gcc main.c -lpthread -o test

clean:
	rm -f test main.o
