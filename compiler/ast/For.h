#ifndef FOR_H
#define FOR_H

#include <string>
#include "Command.h"
#include "Expression.h"
#include "../utilityClasses/CommandWrapper.h"
#include "../utilityClasses/CodeContainer.h"
#include "../utilityClasses/SymbolTable.h"


class For : public Command, public WrapperCallback
{
  Expression* init;
  Expression* condition;
  Expression* update;
  Command* body;
  public:
    For(int line, Expression* init, Expression* cond, Expression* update, Command* body) 
      : Command(line), init(init), condition(cond), update(update), body(body) { }
    std::string explain(int ind);
    void generate(CodeContainer*, SymbolTable*);
    void genEpilogue(CodeContainer*, SymbolTable*);
};

#endif
