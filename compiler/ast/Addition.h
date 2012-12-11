#ifndef ADDITION_H
#define ADDITION_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Addition: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Addition(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //ADDITION_H
