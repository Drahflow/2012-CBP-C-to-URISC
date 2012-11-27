#ifndef GREATEROREQUAL_H
#define GREATEROREQUAL_H

#include "Command.h"

class GreaterOrEqual: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	GreaterOrEqual(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //GREATEROREQUAL_H
