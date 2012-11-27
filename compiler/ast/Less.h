#ifndef LESS_H
#define LESS_H

#include "Command.h"

class Less: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Less(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //LESS_H
