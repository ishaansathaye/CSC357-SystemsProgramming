CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = fe_test
OBJS = fe_test.o

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fs_emulator.o : fe_test.c
	$(CC) $(CFLAGS) -c fe_test.c

clean :
	rm *.o $(MAIN) core
