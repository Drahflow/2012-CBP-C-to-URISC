#ifndef LESSOREQUAL_H
#define LESSOREQUAL_H

#include "Command.h"

class LessOrEqual: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	LessOrEqual(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //LESSOREQUAL_H
