#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H

#include <string>
#include <vector>
#include "Expression.h"
#include "Command.h"

class FunctionCall: public Expression
{
	public:
	std::vector<Expression*>* values_;
	char* name_;
	FunctionCall(int line, char* name, std::vector<Expression *>* values) : Expression(line) { values_ = values; name_ = name;}
	std::string explain(int ind);
};

#endif //FUNCTIONCALL_H
