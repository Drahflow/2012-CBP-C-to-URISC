#include <string>
#include <sstream>
#include "Return.h"

#include "../utilityClasses/CodeContainer.h"
#include "../utilityClasses/SymbolTable.h"

using namespace std;

string Return::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "return, value:" << endl;
  expl << value->explain(ind + 1);
  return expl.str();
}

void Return::generate(CodeContainer *code, SymbolTable *symbols)
{
	value->generate(code, symbols);
	int deltaAddr = code->allocate();
	code->addClearAkk();
	code->push_back(deltaAddr);
	code->push_back(0);
	code->initStatic(deltaAddr, code->address() - 1 - symbols->resolveVariable(" functionReturn").addr);
}
