#ifndef WHILE_H
#define WHILE_H

#include <string>
#include "Expression.h"
#include "Command.h"
#include "../utilityClasses/CommandWrapper.h"

class While : public Command, public WrapperCallback
{
  Expression* condition;
  Command* body;
  // stores memory for jump delta
  int beginLoopAddr;
  unsigned short pcBeginLoop;
  
  public:
    While(int line, Expression* cond, Command* body) : Command(line), condition(cond), body(body) { }
    std::string explain(int ind);
    void generate(CodeContainer*, SymbolTable*);
    void genEpilogue(CodeContainer*, SymbolTable*);
};

#endif
