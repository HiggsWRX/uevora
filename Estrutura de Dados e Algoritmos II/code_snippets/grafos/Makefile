CC = gcc        # compilador a usar
CFLAGS = -g     # flags do compilador, para debugging, etc
LDFLAGS =       # flags do linker, (p.ex. -lm, -lcrypto, etc)


EXECUTABLE = grafosmain    # nome do executável a gerar

# main target
all: $(EXECUTABLE)

# object files (.o)
grafo.o: grafo.h grafo.c
	$(CC) $(CFLAGS) -c grafo.c

grafosmain.o: grafo.h grafosmain.c
	$(CC) $(CFLAGS) -c grafosmain.c

grafosmain: grafo.o grafosmain.o
	$(CC) $(CFLAGS) -o $@ grafo.o grafosmain.o

clean:
	rm -f *.o

clean-all clean_all: clean
	rm -f *~ $(EXECUTABLE)
