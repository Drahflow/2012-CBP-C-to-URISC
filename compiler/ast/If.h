#ifndef IF_H
#define IF_H

#include <string>
#include "Command.h"
#include "Expression.h"
#include "../utilityClasses/CodeContainer.h"
#include "../utilityClasses/SymbolTable.h"

class If : public Command
{
  Expression* condition;
  Command* thenBranch;
  Command* elseBranch;

  void allocateStatic(CodeContainer* code);
  
    static int zeroAddr;
    static int minOneAddr;
  public:
    If(int line, Expression* cond, Command* then, Command* els = NULL) 
      : Command(line), condition(cond), thenBranch(then), elseBranch(els) {  }
    std::string explain(int ind);
    void generate(CodeContainer*, SymbolTable*);
};

#endif
