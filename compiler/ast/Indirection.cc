#include <string>
#include <sstream>
#include "Indirection.h"

using namespace std;

string Indirection::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "Indirection:" << endl;
  expl << indent(ind) << "-expression:" << endl;
  expl << expr->explain(ind + 1);
  return expl.str();
}

void Indirection::generate(CodeContainer *code, SymbolTable *symbols) {
  expr->generate(code, symbols);

  int addr = code->address();
  code->addComment("indirect memory access");
  code->push_back(code->clearAddr);
  code->push_back(code->clearAddr);
  code->push_back(code->clearAddr); // clear = acc = 0
  code->push_back(addr + 13);
  code->push_back(addr + 13); // code = 0
  code->push_back(code->exprResultAddr); // acc = expr
  code->push_back(code->clearAddr); // clear = acc = -expr
  code->push_back(code->clearAddr); // skipped (or expr == 0)
  code->push_back(addr + 13); // code = acc = expr
  code->push_back(code->exprResultAddr); // acc = expr = 0 or skipped
  code->push_back(code->exprResultAddr); // acc = expr = 0 or skipped
  code->push_back(code->clearAddr);
  code->push_back(code->clearAddr); // clear = acc = 0
  code->push_back(0xEEEE); // self modified // acc = *(original expr)
  code->push_back(code->clearAddr); // clear = acc = -*(original expr)
  code->push_back(code->clearAddr); // skipped (or *(original expr) == 0)
  code->push_back(code->exprResultAddr); // expr = acc = --*(original expr)
}
