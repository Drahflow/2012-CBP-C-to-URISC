#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Subtraction: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Subtraction(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //SUBTRACTION_H
