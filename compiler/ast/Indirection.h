#ifndef INDIRECTION_H
#define INDIRECTION_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Indirection: public Expression
{
	public:
	Expression * augend;
	Indirection(int line, Expression *e) : Expression(line) { augend = e; }
	std::string explain(int ind);
};

#endif //INDIRECTION_H
