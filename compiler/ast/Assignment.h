#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Assignment: public Expression
{
	public:
	Expression * augend;
	char* name_;
	Assignment(int line, char* name, Expression *e) : Expression(line) { augend = e; name_ = name;}
	std::string explain(int ind);
};

#endif //ASSIGNMENT_H
