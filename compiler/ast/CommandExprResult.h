#ifndef COMMANDEXPRRESULT_H
#define COMMANDEXPRRESULT_H

#include <string>
#include "Expression.h"
#include "Command.h"

class CommandExprResult : public Command
{
  Expression* value;
  public:
    CommandExprResult(int line, Expression* value) : Command(line), value(value) { }
    std::string explain(int ind) { value->explain( ind ); }
    void generate(CodeContainer *code, SymbolTable * symbols) { value->generate( code, symbols ); }
};

#endif
