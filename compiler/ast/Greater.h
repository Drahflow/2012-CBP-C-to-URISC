#ifndef GREATER_H
#define GREATER_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Greater: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Greater(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //GREATER_H
