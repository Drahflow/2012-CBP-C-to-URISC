#ifndef OR_H
#define OR_H

#include "Command.h"

class Or: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Or(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //OR_H
