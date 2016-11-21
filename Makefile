CC=gcc
CFLAGS= -Wall --std=c99

hello: main.o my_string.o
	$(CC) $(CFLAGS) -o hello my_string.o main.o
main.o: main.c
	$(CC) $(CFLAG) -c main.c
string.o: my_string.c
	$(CC) $(CFLAG) -c string.c
clean:
	rm hello main.o my_string.o