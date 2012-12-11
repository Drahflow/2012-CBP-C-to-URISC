#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Multiplication: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Multiplication(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //MULTIPLICATION_H
