#ifndef ARRAYSUBSCRIPT_H
#define ARRAYSUBSCRIPT_H

#include <string>
#include "Expression.h"
#include "Command.h"

class ArraySubscript: public Expression
{
	public:
	Expression * augend;
	char* name_;
	ArraySubscript(int line, char* name, Expression *e) : Expression(line) { augend = e; name_ = name;}
	std::string explain(int ind);
};

#endif //ARRAYSUBSCRIPT_H
