#ifndef LESSOREQUAL_H
#define LESSOREQUAL_H

#include <string>
#include "Expression.h"
#include "Command.h"

class LessOrEqual: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	LessOrEqual(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
	void generate(CodeContainer *code, SymbolTable *table);
};

#endif //LESSOREQUAL_H
