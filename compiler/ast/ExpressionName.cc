#include <string>
#include <sstream>
#include "ExpressionName.h"

using std::endl;

std::string ExpressionName::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "ExpressionName:" << endl;
  expl << indent(ind) << name << endl;
  return expl.str();
}

void ExpressionName::generate(CodeContainer *code, SymbolTable *symbols) {
  const SymbolTable::Variable &var = symbols->resolveVariable(name);

  code->addComment("access to " + name);

  if(var.global) {
    code->addClear(code->exprResultAddr);
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr);
    code->addLoad(var.addr);
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr);
    code->push_back(code->exprResultAddr);
  } else {
    code->addClear(code->exprResultAddr);
    code->push_back(code->allocate(var.addr));
    code->push_back(code->exprResultAddr); // expr = -addr
    code->addLoad(code->stackPointerAddr);
    code->push_back(code->clearAddr); // *clearAddr = - *stackPointerAddr
    code->push_back(code->clearAddr); // skipped
    code->push_back(code->exprResultAddr); // expr = stack pointer - addr

    int addr = code->address();
    code->addComment("indirect memory access NAME");
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr); // clear = acc = 0
    code->push_back(addr + 12);
    code->push_back(addr + 12); // code = 0
    code->push_back(code->exprResultAddr); // acc = expr
    code->push_back(code->clearAddr); // clear = acc = -expr
    code->push_back(code->clearAddr); // skipped (or expr == 0)
    code->push_back(addr + 12); // code = acc = expr
    code->push_back(code->exprResultAddr); // acc = expr = 0
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr); // clear = acc = 0
    code->push_back(0xEEEE); // self modified // acc = *(original expr)
    code->push_back(code->clearAddr); // clear = acc = -*(original expr)
    code->push_back(code->clearAddr); // skipped (or *(original expr) == 0)
    code->push_back(code->exprResultAddr); // expr = acc = --*(original expr)
  }
}
