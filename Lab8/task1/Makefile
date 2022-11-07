CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
MAIN = timeout
OBJS = my_timeout.o

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

my_timeout.o : my_timeout.c
	$(CC) $(CFLAGS) -c my_timeout.c

clean :
	rm *.o $(MAIN) core
