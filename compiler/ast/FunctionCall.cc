#include <string>
#include <sstream>
#include "FunctionCall.h"

using std::endl;

std::string FunctionCall::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "FunctionCall:" << endl;
//  expl << indent(ind) << "-expression:" << endl;
//  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-to NAME:" << endl;
  expl << name_;
  return expl.str();
}

void FunctionCall::generate(CodeContainer* code, SymbolTable* symbols)
{
	code->addComment("start functionCall");
	SymbolTable::Variable functionVariable = symbols->resolveVariable( name_ );
	int functionAddress = code->allocate( functionVariable.addr );
	std::vector<Expression*>::reverse_iterator rit; // reverse iterator
	int valueSize = values_->size();
	code->addComment("put expressions to the stack");
	for(rit = values_->rbegin(); rit!=values_->rend(); ++rit) 
	{
		(*rit)->generate(code, symbols);
		code->addStackPush( code->exprResultAddr ); //pushes parameters for the function to the stack
	}// perform jump

	code->addClearAkk();
	int retAddrAddr = code->address()+2;
	code->push_back( retAddrAddr ); // load 1 to akk
	code->push_back( code->clearAddr ); // run 0-1 and skip next
	int retPosition = code->size();
	code->push_back( 1 ); // skipped
	code->push_back( code->tempAddr ); // clear temp
	code->push_back( code->tempAddr );
	code->push_back( code->tempAddr );
	code->push_back( code->clearAddr ); // *clearAddr = 0
	code->push_back( code->clearAddr );
	code->push_back( retAddrAddr ); //load *oneAddr to akk
	code->push_back( code->clearAddr ); // put 0-(*oneAddr) to temp
	code->push_back( code->clearAddr ); // skipped
	code->push_back( code->tempAddr ); // *tempAddr = *retAddrAddr
	code->addClearAkk();
	code->addStackPush( code->tempAddr ); // pushes return Address to stack.
	code->addNOP();
	code->addComment("perform jump to function");
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( code->clearAddr );
	code->push_back( functionAddress ); // write address to akk
	code->push_back( code->address() + 2 );
	code->push_back( 0 ); // perform jump
	//code->address();
	code->push_back( code->address() - 1 );
	code->addNOP(); // NOP for non-determinitic backjump
	code->setInstruction( retPosition, code->address() );
	code->addComment("return Code from functionCall");
//    CodeContainer::Instruction instr;
//	instr.code = code->address();
//	code->codeContainer[retPosition] = instr;
	code->addNOP(); // 

	code->addComment("pop the parameters from stack");
	code->addStackPop( code->tempAddr ); //pops return address from stack
	for(rit = values_->rbegin(); rit!=values_->rend(); ++rit) 
	{
		code->addStackPop( code->tempAddr ); //pops parameters from stack
	}
}
