#include <string>
#include <sstream>
#include "Less.h"
#include "Greater.h"

using std::endl;

std::string Less::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Less:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void Less::generate(CodeContainer *code, SymbolTable *table) {
	Greater *greater =  new Greater( 0, addend, augend );
	greater->generate( code, table );
}
