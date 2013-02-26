#include <string>
#include <sstream>
#include "Assignment.h"

using std::endl;

std::string Assignment::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Assignment:" << endl;
  expl << indent(ind) << "-expression:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-to NAME:" << endl;
  expl << indent(ind + 1) << name_ << endl;
  return expl.str();
}

void Assignment::generate(CodeContainer *code, SymbolTable *table)
{
	code->addComment("Assignment");
	augend->generate(code, table); // evaluated the expression on the right side of the =
	SymbolTable::Variable variable = table->resolveVariable( name_ );
	code->addNOP();
	if( variable.global ) {
		code->addClear( variable.addr );
		code->addClear( code->clearAddr );
		code->push_back( code->exprResultAddr ); // *exprResultAddr - 0
		code->push_back( code->clearAddr ); // 0 - *exprResultAddr 
		code->push_back( variable.addr ); // skipped if *exprResultAddr is non-zero, if it is not skipped, put 0 to variable->addr
		code->push_back( variable.addr ); //
	}
	else {
		code->addComment("local Variable Assignment");
		//code->push_back(0xDEB6);
		code->addStackPush(code->exprResultAddr); // pushes exprResult to stack
		// calculation of the variable address:
		code->addComment("get local variable address");
		code->addClear(code->tempAddr);
		code->push_back(code->allocate(variable.addr));
		code->push_back(code->tempAddr); // expr = -addr
		code->addLoad(code->functionStackPointerAddr); // akk = *functionStackPointerAddr
		code->push_back(code->clearAddr); // akk = 0 - *functionStackPointerAddr
		code->push_back(code->clearAddr); // skipped or zero
		code->push_back(code->tempAddr); // expr = stack pointer - addr
		code->push_back(code->clearAddr); // skipped or not
		//code->push_back( 0xDEB6 ); //debug output
		// move  exprResult to variable address in code->tempAddr
		code->addComment("move exprResult local variable address");
		code->addStackPop(code->exprResultAddr); // pops the right expr result to tempAddr
		code->addClearAkk();
		int localAddr = code->address();
		code->push_back(localAddr + 30);
		code->push_back(localAddr + 30);
		code->push_back(localAddr + 30);
		code->push_back(code->tempAddr);
		code->push_back( code->clearAddr ); // 0 - *tempAddr
		code->push_back( code->clearAddr ); // skipped or zero
		code->push_back(localAddr + 30);
		code->push_back( code->clearAddr );
		code->push_back( code->clearAddr );
		code->push_back( code->clearAddr );
		code->push_back(localAddr + 31);
		code->push_back(localAddr + 31);
		code->push_back(localAddr + 31);
		code->push_back(code->tempAddr);
		code->push_back( code->clearAddr ); // 0 - *tempAddr
		code->push_back( code->clearAddr ); // skipped or zero
		code->push_back(localAddr + 31);
		code->push_back( code->clearAddr );
		code->push_back( code->clearAddr );
		code->push_back( code->clearAddr );
		code->push_back(localAddr + 32);
		code->push_back(localAddr + 32);
		code->push_back(localAddr + 32);
		code->push_back(code->tempAddr);
		code->push_back( code->clearAddr ); // 0 - *tempAddr
		code->push_back( code->clearAddr ); // skipped or zero
		code->push_back(localAddr + 32);
		code->push_back( code->clearAddr );
		code->push_back( code->clearAddr );
		code->push_back( code->clearAddr );
		code->push_back( 0xeeee ); // get overwritten to clear stackaddress
		code->push_back( 0xeeee );
		code->push_back( 0xeeee );
		localAddr = code->address();
		code->push_back(localAddr + 14);
		code->push_back(localAddr + 14);
		code->push_back(localAddr + 14);
		code->push_back(code->tempAddr);
		code->push_back( code->clearAddr ); // 0 - *tempAddr
		code->push_back( code->clearAddr ); // skipped or zero
		code->push_back(localAddr + 14);
		code->push_back( code->clearAddr ); //
		code->push_back( code->clearAddr ); //
		code->push_back( code->clearAddr ); //
		code->push_back( code->clearAddr ); //
		code->push_back(code->exprResultAddr); // load result of the right expression
		code->push_back(code->clearAddr); // store -(*addr) in akk and borrow
		code->push_back(code->clearAddr); // skip, or zero
		//int oneAddr = localAddr + 7;
		code->addComment("local Variable Assignment assignment");
		code->push_back( 0xeeee ); // store *addr at the pointer position
		code->push_back(code->clearAddr); //
		//code->push_back(0xDEB6);
		code->push_back(code->clearAddr); //
	}
	code->addNOP();
}
