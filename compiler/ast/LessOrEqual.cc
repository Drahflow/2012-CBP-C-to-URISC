#include <string>
#include <sstream>
#include "LessOrEqual.h"
#include "Greater.h"
#include "Not.h"

using std::endl;

std::string LessOrEqual::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "LessOrEqual:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}


void LessOrEqual::generate(CodeContainer *code, SymbolTable *table) {
		// a <= b is the same as !( a > b )
	Greater *greater =  new Greater( 0, augend, addend );
	Not *nott = new Not( 0, greater );
	nott->generate( code, table );
}
