CC = gcc        # compilador a usar
CFLAGS = -g     # flags do compilador, para debugging, etc
LDFLAGS =       # flags do linker, (p.ex. -lm, -lcrypto, etc)

EXECUTABLE = trabalho1    # nome do executável a gerar

# main target
all: $(EXECUTABLE)

# object files (.o)
btree.o: btree.h btree.c
	$(CC) $(CFLAGS) -c btree.c

trie.o: trie.h trie.c
	$(CC) $(CFLAGS) -c trie.c

trabalho1.o: btree.h trie.h trabalho1.c
	$(CC) $(CFLAGS) -c trabalho1.c

trabalho1: btree.o trie.o trabalho1.o
	$(CC) $(CFLAGS) -o $@ btree.o trie.o trabalho1.o
	
clean:
	rm -f *.o

clean-all clean_all: clean
	rm -f *~ $(EXECUTABLE)

run:
	./$(EXECUTABLE)