CC = gcc        # compilador a usar
CFLAGS = -g     # flags do compilador, para debugging, etc
LDFLAGS =       # flags do linker, (p.ex. -lm, -lcrypto, etc)


EXECUTABLE = mainscheduler    # nome do executável a gerar

# main target
all: $(EXECUTABLE)

# object files (.o)
linkedlist.o: linkedlist.h linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c
scheduler.o: scheduler.h scheduler.c
	$(CC) $(CFLAGS) -c scheduler.c
mainscheduler.o: linkedlist.h scheduler.h mainscheduler.c
	$(CC) $(CFLAGS) -c mainscheduler.c
mainscheduler: linkedlist.o scheduler.o mainscheduler.o
	$(CC) $(CFLAGS) -o $@ linkedlist.o scheduler.o mainscheduler.o
clean:
	rm -f *.o
clean-all clean_all: clean
	rm -f *~ $(EXECUTABLE)