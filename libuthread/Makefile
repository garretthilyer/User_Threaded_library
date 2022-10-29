# Target library
lib := libuthread.a
OBJ := queue.o context.o uthread.o #preempt.o sem.o 

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CPLAGS += -g

all: $(lib)

libuthread.a: $(OBJ) 
	ar rcs $@ $(OBJ)

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

context.o: context.c private.h uthread.h
	$(CC) $(CFLAGS) -c -o $@ $<

preempt.o: preempt.c private.h uthread.h
	$(CC) $(CFLAGS) -c -o $@ $<

sem.o: sem.c queue.h private.h sem.h
	$(CC) $(CFLAGS) -c -o $@ $<

uthread.o: uthread.c private.h uthread.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ) $(lib)
