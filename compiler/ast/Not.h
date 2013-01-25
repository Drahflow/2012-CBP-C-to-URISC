#ifndef NOT_H
#define NOT_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Not: public Expression
{
	public:
	Expression * augend;
	Not(int line, Expression *e1) : Expression(line) { augend = e1;}
	std::string explain(int ind);
	void generate(CodeContainer*, SymbolTable*);
};

#endif //NOT_H
