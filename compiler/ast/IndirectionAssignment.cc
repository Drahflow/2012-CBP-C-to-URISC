#include <string>
#include <sstream>
#include "IndirectionAssignment.h"

using std::endl;

std::string IndirectionAssignment::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Assignment:" << endl;
  expl << indent(ind) << "-expression:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-to pointer adress:" << endl;
  expl << pointer_->explain(ind + 1);;
  return expl.str();
}


void IndirectionAssignment::generate(CodeContainer* code, SymbolTable* table)
{
	code->addComment( "IndirectionAssignment start" );
	augend->generate(code, table); // evaluated the expression on the right side of the =
	code->addStackPush(code->exprResultAddr); // pushes exprResult to stack

	pointer_->generate(code, table); // evalutes the pointer address
	code->addStackPop(code->tempAddr); // pops the right expr result to tempAddr
	code->addClearAkk();
	code->addComment( "IndirectionAssignment assignment" );
	int localAddr = code->address();
	code->push_back(localAddr + 30);
	code->push_back(localAddr + 30);
	code->push_back(localAddr + 30);
	code->push_back(code->exprResultAddr);
	code->push_back( code->clearAddr ); // 0 - *exprResultAddr
	code->push_back( code->clearAddr ); //skipped or zero
	code->push_back(localAddr + 30);
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back(localAddr + 31);
	code->push_back(localAddr + 31);
	code->push_back(localAddr + 31);
	code->push_back(code->exprResultAddr);
	code->push_back( code->clearAddr ); // 0 - *exprResultAddr
	code->push_back( code->clearAddr ); //skipped or zero
	code->push_back(localAddr + 31);
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back(localAddr + 32);
	code->push_back(localAddr + 32);
	code->push_back(localAddr + 32);
	code->push_back(code->exprResultAddr);
	code->push_back( code->clearAddr ); // 0 - *exprResultAddr
	code->push_back( code->clearAddr ); //skipped or zero
	code->push_back(localAddr + 32);
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( 0xeeee ); // get overwritten to clear stackaddress
	code->push_back( 0xeeee );
	code->push_back( 0xeeee );
	localAddr = code->address();
	code->push_back(localAddr + 14);
	code->push_back(localAddr + 14);
	code->push_back(localAddr + 14);
	code->push_back(code->exprResultAddr); // load *exprResultAddr
	code->push_back( code->clearAddr ); // 0 - *exprResultAddr
	code->push_back( code->clearAddr ); // skipped or zero
	code->push_back(localAddr + 14);  // 0 - (0 - *exprResultAddr)
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back( code->clearAddr ); //clear *clearAddr and akk
	code->push_back(code->tempAddr); // load result of the right expression
	code->push_back(code->clearAddr); // store -(*addr) in akk and borrow
	code->push_back(1); // skip, use the 1 later
	//int oneAddr = localAddr + 7;
	code->push_back( 0xeeee ); // store *addr at the pointer position

	
}
