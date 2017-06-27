CC = gcc
CFLAGS = -g
OUTFILE = lambda
LIBS = -lm


all: parser.c lexer.c apt.c ll.c reductions.c
	$(CC) $(CFLAGS) parser.c lexer.c apt.c ll.c reductions.c -o $(OUTFILE) $(LIBS)

parser.c: $(OUTFILE).y
	bison -y -d $(OUTFILE).y -o parser.c

lexer.c: $(OUTFILE).lex
	flex -o lexer.c $(OUTFILE).lex

clean: 
	rm -rf parser.c lexer.c parser.h
	rm -f *~
	rm -f *.o
	rm -f calc
