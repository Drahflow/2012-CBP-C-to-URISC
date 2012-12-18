#ifndef INDIRECTIONASSIGNMENT_H
#define INDIRECTIONASSIGNMENT_H

#include <string>
#include "Expression.h"
#include "Command.h"

class IndirectionAssignment: public Expression
{
	public:
	Expression * pointer_;
	Expression * augend;
	IndirectionAssignment(int line, Expression * pointer, Expression *e) : Expression(line) { augend = e; pointer_ = pointer;}
	std::string explain(int ind);
};

#endif //INDIRECTIONASSIGNMENT_H
