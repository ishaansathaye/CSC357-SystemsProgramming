CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
MAIN = f_test
OBJS = f_test.o

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

f_test.o : f_test.c
	$(CC) $(CFLAGS) -c f_test.c

clean :
	rm *.o $(MAIN) core
