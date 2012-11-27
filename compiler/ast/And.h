#ifndef AND_H
#define AND_H

#include "Command.h"

class And: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	And(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //AND_H
