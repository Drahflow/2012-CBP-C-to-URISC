#ifndef EXPRESSIONNAME_H
#define EXPRESSIONNAME_H

#include "Expression.h"
#include "Command.h"

#include <string>

class ExpressionName: public Expression {
  private:
    const std::string name;

  public:
    ExpressionName(int line, char* name): Expression(line), name(name) { }
    std::string explain(int ind);
    void generate(CodeContainer *, SymbolTable *);
};

#endif //EXPRESSIONNAME_H
