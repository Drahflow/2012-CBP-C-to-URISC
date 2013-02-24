#include <string>
#include <sstream>
#include "Greater.h"
#include "ExpressionEmpty.h"
#include "ExpressionNum.h"
#include "CommandExprResult.h"
#include "If.h"

using std::endl;

std::string Greater::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Greater:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void Greater::generate(CodeContainer *code, SymbolTable *symbols)
{
// augend > addend
// idea: (a > b) -> a-b borrows if false, so we can write a number into a cell at the skipped position, then use if;
	code->addComment("Greater");
	augend->generate( code, symbols );
	code->addStackPush( code->exprResultAddr );
	addend->generate( code, symbols ); // put augend to exprResultAddr
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr ); // clear *clearAddr
	code->push_back( code->tempAddr );
	code->push_back( code->tempAddr ); // clear *tempAddr
	code->push_back( code->exprResultAddr ); // a = *exprResultAddr
	code->push_back( code->tempAddr ); // 0 - a
	code->push_back( code->tempAddr ); // skipped (or its already 0)
	code->push_back( code->clearAddr ); // 0 - (0 - a ) = a
	code->push_back( code->exprResultAddr );
	code->push_back( code->exprResultAddr );
	code->push_back( code->exprResultAddr ); // clear akk and *exprResultAddr
	code->push_back( code->clearAddr ); // akk = a
	code->push_back( code->exprResultAddr ); // *exprResultAddr = -a
	code->push_back( code->exprResultAddr ); // skipped or zero
	code->addStackPop( code->tempAddr ); // put addend to tempAddr = b
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr ); // clear clearAddr
	code->push_back( code->exprResultAddr ); // akk = -a
	code->push_back( code->clearAddr ); // *clearAddr = a
	code->push_back( code->exprResultAddr ); // 
	code->push_back( code->exprResultAddr ); // 
	code->push_back( code->exprResultAddr ); // 
	code->push_back( code->exprResultAddr ); // clear *exprResultAddr and akk
	code->push_back( code->clearAddr ); // akk = a
	code->push_back( code->tempAddr );  // akk = b - a skips (or zero) if a>b is false
	code->push_back( code->exprResultAddr ); // if b==a its 0, if a>b is true its 0 - (b-a)
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr ); // NOP
	// now: if a>b is true, *exprResultAddr is non-zero, otherwise its zero
	Expression *empty = new ExpressionEmpty( 0 );
	Command *one  = new CommandExprResult( 0, new ExpressionNum( 0, 1 ) );
	Command *zero = new CommandExprResult( 0, new ExpressionNum( 0, 0 ) );
	If *iff = new If( 0, empty, one, zero );
	iff->generate( code, symbols );
}
