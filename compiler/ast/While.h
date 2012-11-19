#ifndef WHILE_H
#define WHILE_H

#include <string>
#include "Expression.h"
#include "Command.h"

class While : public Command
{
  Expression* condition;
  Command* body;
  public:
    While(int line, Expression* cond, Command* body) : Command(line), condition(cond), body(body) { }
    std::string explain(int ind);
};

#endif
