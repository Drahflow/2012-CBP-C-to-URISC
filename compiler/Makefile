SRC=$(wildcard *.cc) $(wildcard ast/*.cc)
EXCL=simple_c.tab.cc simple_c.lex.cc

OBJ=simple_c.tab.o simple_c.lex.o $(patsubst %.cc, %.o, $(filter-out $(EXCL), $(SRC)))

all: compiler

compiler: $(OBJ)
	g++ $(OBJ) -o compiler

-include $(OBJ:%.o=%.d)

%.o: %.cc
	g++ -c $*.cc -o $*.o
	g++ -MM $*.cc > $*.d

simple_c.tab.cc: simple_c.y
	bison -d simple_c.y -o simple_c.tab.cc

simple_c.lex.cc: simple_c.l
	flex -o simple_c.lex.cc simple_c.l

clean:
	rm compiler simple_c.tab.hh simple_c.tab.cc simple_c.lex.cc *.o ast/*.o *.d ast/*.d
