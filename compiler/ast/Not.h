#ifndef NOT_H
#define NOT_H

#include "Command.h"

class Not: public Expression
{
	public:
	Expression * augend;
	Not(int line, Expression *e1) : Expression(line) { augend = e1;}
};

#endif //NOT_H
