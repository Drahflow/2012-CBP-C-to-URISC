#ifndef EXPRESSIONNUM_H
#define EXPRESSIONNUM_H

#include <string>
#include "Expression.h"
#include "Command.h"

class ExpressionNum: public Expression
{
	public:
	int num_;
	ExpressionNum(int line, int num) : Expression(line) { num_ = num;}
	std::string explain(int ind);
};

#endif //EXPRESSIONNUM_H
