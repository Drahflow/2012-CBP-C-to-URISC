#include <string>
#include <sstream>
#include "Not.h"
#include "If.h"
#include "CommandExprResult.h"
#include "ExpressionNum.h"

using std::endl;

std::string Not::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Not:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  return expl.str();
}

void Not::generate(CodeContainer *code, SymbolTable *table)
{
// idea: (!a) -> if(a) return 0; else return 1;
	Command *one  = new CommandExprResult( 0, new ExpressionNum( 0, 1 ) );
	Command *zero = new CommandExprResult( 0, new ExpressionNum( 0, 0 ) );
	If *iff = new If( 0, augend, zero, one );
	iff->generate( code, table );

}
