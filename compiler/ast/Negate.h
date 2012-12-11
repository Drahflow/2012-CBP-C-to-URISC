#ifndef NEGATE_H
#define NEGATE_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Negate: public Expression
{
	public:
	int neg_;
	Negate(int line, int neg) : Expression(line) { neg_ = neg;}
	std::string explain(int ind);
};

#endif //NEGATE_H
