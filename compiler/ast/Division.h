#ifndef DIVISION_H
#define DIVISION_H

#include "Command.h"

class Division: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Division(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
};

#endif //DIVISION_H
