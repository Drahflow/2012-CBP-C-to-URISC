#include <string>
#include <sstream>
#include "Equal.h"
#include "Subtraction.h"
#include "If.h"
#include "CommandExprResult.h"
#include "ExpressionNum.h"

using std::endl;

std::string Equal::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Equal:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void Equal::generate(CodeContainer *code, SymbolTable *table)
{
// idea: (a == b) -> if(a-b) return 0; else return 1;
	code->addComment( "Equal" );
	Expression *sub = new Subtraction( 0, augend, addend );
	Command *one  = new CommandExprResult( 0, new ExpressionNum( 0, 1 ) );
	Command *zero = new CommandExprResult( 0, new ExpressionNum( 0, 0 ) );
	If *iff = new If( 0, sub, zero, one );
	iff->generate( code, table );
}
