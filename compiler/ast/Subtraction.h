#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "Command.h"

class Subtraction: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Subtraction(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //SUBTRACTION_H
