#ifndef LESS_H
#define LESS_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Less: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	Less(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //LESS_H
