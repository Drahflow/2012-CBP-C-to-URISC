#ifndef DIVISION_H
#define DIVISION_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Division: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Division(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //DIVISION_H
