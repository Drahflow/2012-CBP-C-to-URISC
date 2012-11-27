#ifndef ADDITION_H
#define ADDITION_H

#include "Command.h"

class Addition: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Addition(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //ADDITION_H
