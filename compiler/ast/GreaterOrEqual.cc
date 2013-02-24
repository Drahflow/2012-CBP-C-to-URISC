#include <string>
#include <sstream>
#include "GreaterOrEqual.h"
#include "Greater.h"
#include "Not.h"

using std::endl;

std::string GreaterOrEqual::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "GreaterOrEqual:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void GreaterOrEqual::generate(CodeContainer *code, SymbolTable *table) {
	code->addComment( "GreaterOrEqual" );
	Greater *greater =  new Greater( 0, addend, augend );
	Not *nott = new Not( 0, greater );
	nott->generate( code, table );
}
