#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Command.h"

class Expression : public Command
{
	public:
	Expression(int line) : Command(line) {}
};

#endif
