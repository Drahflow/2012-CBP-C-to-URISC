#include <string>
#include <sstream>
#include "Subtraction.h"

using std::endl;

std::string Subtraction::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Subtraction:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void Subtraction::generate(CodeContainer* code, SymbolTable* table)
{
	code->addComment("=== Subtraction Start ===");
	addend->generate(code, table);
	code->addStackPush(code->exprResultAddr);
	augend->generate(code, table);
	code->push_back(code->clearAddr);
	code->push_back(code->clearAddr);
	code->push_back(code->clearAddr);
	code->addStackPop(code->tempAddr);
	code->addClearAkk();
	code->push_back(code->tempAddr);
	code->push_back(code->exprResultAddr);
	code->addNOP();
	code->addComment("=== Subtraction End ===");
}
