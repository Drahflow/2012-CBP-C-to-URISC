#ifndef EXPRESSIONNAME_H
#define EXPRESSIONNAME_H

#include "Command.h"

class ExpressionName: public Expression
{
	public:
	char *name_;
	ExpressionName(int line, char* name) : Expression(line) { name_ = name;}
};

#endif //EXPRESSIONNAME_H
