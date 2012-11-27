#ifndef NEGATE_H
#define NEGATE_H

#include "Command.h"

class Negate: public Expression
{
	public:
	int neg_;
	Negate(int line, int neg) : Expression(line) { neg_ = neg;}
};

#endif //NEGATE_H
