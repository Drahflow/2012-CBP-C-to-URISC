#ifndef NOTEQUAL_H
#define NOTEQUAL_H

#include <string>
#include "Expression.h"
#include "Command.h"

class NotEqual: public Expression
{
	public:
	Expression * augend;
	Expression * addend;
	NotEqual(int line, Expression *e1, Expression *e2) : Expression(line) { augend = e1; addend = e2;}
	std::string explain(int ind);
};

#endif //NOTEQUAL_H
