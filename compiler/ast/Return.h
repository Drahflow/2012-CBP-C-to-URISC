#ifndef RETURN_H
#define RETURN_H

#include "Expression.h"
#include "Command.h"

class Return : public Command
{
  Expression* value;
  public:
    Return(int line, Expression* value) : Command(line), value(value) { }

};

#endif
