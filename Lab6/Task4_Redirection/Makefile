CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = to_file
OBJS = to_file.o

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

to_file.o : to_file.c
	$(CC) $(CFLAGS) -c to_file.c

clean :
	rm *.o $(MAIN) core
