CC = gcc        # compilador a usar
CFLAGS = -g     # flags do compilador, para debugging, etc
LDFLAGS =       # flags do linker, (p.ex. -lm, -lcrypto, etc)


EXECUTABLE = btreemain    # nome do executável a gerar

# main target
all: $(EXECUTABLE)

# object files (.o)
btree.o: btree.h btree.c
	$(CC) $(CFLAGS) -c btree.c

btreemain.o: btree.h btreemain.c
	$(CC) $(CFLAGS) -c btreemain.c

btreemain: btree.o btreemain.o
	$(CC) $(CFLAGS) -o $@ btree.o btreemain.o

clean:
	rm -f *.o

clean-all clean_all: clean
	rm -f *~ $(EXECUTABLE)

