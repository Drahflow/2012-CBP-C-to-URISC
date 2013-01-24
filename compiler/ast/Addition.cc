#include <string>
#include <sstream>
#include "Addition.h"

using std::endl;

std::string Addition::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Addition:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void Addition::generate(CodeContainer *code, SymbolTable *table)
{
	addend->generate(code, table);
	code->addStackPush(code->exprResultAddr);
	augend->generate(code, table);
	code->addStackPop(code->tempAddr);
	// change stack pointer by +1
	code->push_back(code->clearAddr);
	code->push_back(code->clearAddr);
	code->push_back(code->clearAddr);
	code->push_back(code->tempAddr); // load *tempAddr to akk
	code->push_back(code->clearAddr); // (0-x)
	code->push_back(1); // skip
	code->push_back(code->exprResultAddr); // (*exprResultAddr) + x
}
