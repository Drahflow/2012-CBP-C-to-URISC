#ifndef GREATEROREQUAL_H
#define GREATEROREQUAL_H

#include <string>
#include "Expression.h"
#include "Command.h"

class GreaterOrEqual: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	GreaterOrEqual(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
	void generate(CodeContainer *code, SymbolTable *table);
};

#endif //GREATEROREQUAL_H
