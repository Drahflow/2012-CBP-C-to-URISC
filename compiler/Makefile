all: compiler
compiler: simple_c.tab.o simple_c.lex.o
simple_c.tab.c: simple_c.y
	bison -d simple_c.y
simple_c.lex.c: simple_c.l
	flex -o simple_c.lex.c simple_c.l

clean:
	rm compiler simple_c.tab.h simple_c.tab.c simple_c.lex.c *.o 
