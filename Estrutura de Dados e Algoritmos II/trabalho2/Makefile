CC = gcc        # compilador a usar
CFLAGS = -g     # flags do compilador, para debugging, etc
LDFLAGS = -lm       # flags do linker, (p.ex. -lm, -lcrypto, etc)

EXECUTABLE = huff    # nome do executável a gerar
EXECUTABLE2 = uhuff

# main target
all: $(EXECUTABLE) $(EXECUTABLE2)

# object files (.o)
structs.o: structs.h structs.c
	$(CC) $(CFLAGS) -c structs.c

huff.o: structs.h huff.c
	$(CC) $(CFLAGS) -c huff.c $(LDFLAGS)

huff: structs.o huff.o
	$(CC) $(CFLAGS) -o $@ structs.o huff.o $(LDFLAGS)

uhuff.o: structs.h uhuff.c
	$(CC) $(CFLAGS) -c uhuff.c $(LDFLAGS)

uhuff: structs.o uhuff.o
	$(CC) $(CFLAGS) -o $@ structs.o uhuff.o $(LDFLAGS)
	
clean:
	rm -f *.o

clean-all clean_all: clean
	rm -f *~ $(EXECUTABLE)

run:
	./$(EXECUTABLE) f.txt && ./$(EXECUTABLE2) f.huff