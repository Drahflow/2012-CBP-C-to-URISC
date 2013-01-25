#ifndef EXPRESSIONEMPTY_H
#define EXPRESSIONEMPTY_H

#include <string>
#include "Expression.h"
#include "Command.h"

class ExpressionEmpty: public Expression
{
  public:
    ExpressionNum(int line)
      : Expression(line) { }

    std::string explain(int ind) { }
    void generate(CodeContainer * code, SymbolTable * table) { }
};

#endif //EXPRESSIONEMPTY_H
