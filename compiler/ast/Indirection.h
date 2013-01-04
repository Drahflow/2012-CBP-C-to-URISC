#ifndef INDIRECTION_H
#define INDIRECTION_H

#include <string>
#include "Expression.h"
#include "Command.h"

class Indirection: public Expression {
  private:
    Expression *expr;

  public:
    Indirection(int line, Expression *expr)
      : Expression(line), expr(expr) { }

    std::string explain(int indent);
    void generate(CodeContainer *, SymbolTable *);
};

#endif //INDIRECTION_H
