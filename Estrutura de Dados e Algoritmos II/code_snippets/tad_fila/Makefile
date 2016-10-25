CC = gcc        # compilador a usar
CFLAGS = -g     # flags do compilador, para debugging, etc
LDFLAGS =       # flags do linker, (p.ex. -lm, -lcrypto, etc)


EXECUTABLE = filademo    # nome do executável a gerar

# main target
all: $(EXECUTABLE)

# object files (.o)
tad_fila.o: tad_fila.h tad_fila.c
	$(CC) $(CFLAGS) -c tad_fila.c

filademo.o: tad_fila.h filademo.c
	$(CC) $(CFLAGS) -c filademo.c

filademo: tad_fila.o filademo.o
	$(CC) $(CFLAGS) -o $@ tad_fila.o filademo.o

clean:
	rm -f *.o

clean-all clean_all: clean
	rm -f *~ $(EXECUTABLE)

