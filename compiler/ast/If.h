#ifndef IF_H
#define IF_H

#include <string>
#include "Command.h"
#include "Expression.h"

class If : public Command
{
  Expression* condition;
  Command* thenBranch;
  Command* elseBranch;
  public:
    If(int line, Expression* cond, Command* then, Command* els = NULL) 
      : Command(line), condition(cond), thenBranch(then), elseBranch(els) { }
    std::string explain(int ind);
};

#endif
