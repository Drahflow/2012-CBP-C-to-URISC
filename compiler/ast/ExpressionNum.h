#ifndef EXPRESSIONNUM_H
#define EXPRESSIONNUM_H

#include "Command.h"

class ExpressionNum: public Expression
{
	public:
	int num_;
	ExpressionNum(int line, int num) : Expression(line) { num_ = num;}
};

#endif //EXPRESSIONNUM_H
