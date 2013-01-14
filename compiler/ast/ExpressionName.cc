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
    code->addComment("TODO local variables not yet implemented as stack layout is unspecified");
    code->push_back(var.addr);
  }
}
