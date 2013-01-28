#ifndef AND_H
#define AND_H

#include <string>
#include "Expression.h"
#include "Command.h"

class And: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	And(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	void generate(CodeContainer *, SymbolTable*);
	std::string explain(int ind);
};



#endif //AND_H
