#ifndef EXPRESSIONNUM_H
#define EXPRESSIONNUM_H

#include <string>
#include "Expression.h"
#include "Command.h"

class ExpressionNum: public Expression
{
  private:
    int num;

  public:
    ExpressionNum(int line, int num)
      : Expression(line), num(num) { }

    std::string explain(int);
    void generate(CodeContainer *, SymbolTable *);
};

#endif //EXPRESSIONNUM_H
