#ifndef EXPRESSIONNAME_H
#define EXPRESSIONNAME_H

#include <string>
#include "Expression.h"
#include "Command.h"

class ExpressionName: public Expression
{
	public:
	char *name_;
	ExpressionName(int line, char* name) : Expression(line) { name_ = name;}
	std::string explain(int ind);
};

#endif //EXPRESSIONNAME_H
