#ifndef GREATER_H
#define GREATER_H

#include "Command.h"

class Greater: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Greater(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //GREATER_H
