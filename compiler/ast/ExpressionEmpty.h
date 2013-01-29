#ifndef EXPRESSIONEMPTY_H
#define EXPRESSIONEMPTY_H

#include <string>
#include "Expression.h"
#include "Command.h"

class ExpressionEmpty: public Expression
{
  public:
    ExpressionEmpty(int line)
      : Expression(line) { }

    std::string explain(int ind) { return ""; }
    void generate(CodeContainer * code, SymbolTable * table) { }
};

#endif //EXPRESSIONEMPTY_H
