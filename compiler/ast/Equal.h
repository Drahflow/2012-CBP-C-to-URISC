#ifndef EQUAL_H
#define EQUAL_H

#include "Command.h"

class Equal: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Equal(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //EQUAL_H
