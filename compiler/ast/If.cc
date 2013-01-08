#include <string>
#include <sstream>
#include "If.h"

using std::endl;

int If::zeroAddr = 0;
int If::minOneAddr = 0;

std::string If::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "if, condition:" << endl;
  expl << condition->explain(ind + 1);
  expl << indent(ind) << "-then:" << endl;
  expl << thenBranch->explain(ind + 1);
  if(elseBranch != NULL)
    expl << endl << indent(ind) << "-else:" << endl << elseBranch->explain(ind + 1);
  return expl.str();
}

void If::allocateStatic(CodeContainer* code)
{
	if(If::zeroAddr < 0 && If::minOneAddr < 0)
		return;
    If::zeroAddr = code->allocate(0);
    If::minOneAddr = code->allocate(0xFFFF); // -1 mod 2^16
}

void If::generate(CodeContainer* code, SymbolTable* table)
{
  // make sure we've allocated our memory used internally
  allocateStatic(code);
  // allocate constant for jump delta of else branch
  int elseBranchAddr = code->allocate();
  // generate code for condition expression
  condition->generate(code, table);
  code->addClear(zeroAddr);
  // the address of the condition value
  int memExprResult = code->exprResultAddr;
  code->addLoad(memExprResult);
  // compute 0 - *memExprResult for conditional jump
  code->push_back(zeroAddr);
  // on *memExprResult == 0 load new pc
  code->push_back(elseBranchAddr);
  code->push_back(zeroAddr);
  // is skipped for *memExprResult != 0
  code->push_back(minOneAddr);
  // jump to else branch
  unsigned short pcOldElse = code->address();
  code->push_back(0);
  // generate then
  thenBranch->generate(code, table);
  int afterStatementAddr = code->allocate();
  code->addLoad(afterStatementAddr);
  // jump to end of statement
  unsigned short pcOldEnd = code->address();
  code->push_back(0);
  // delta = pc_from - pc_to
  code->initStatic(elseBranchAddr, pcOldElse - (unsigned short) code->address());
  // generate else
  if(elseBranch != NULL)
  	elseBranch->generate(code, table);
  code->initStatic(afterStatementAddr, pcOldEnd - ((unsigned short) code->address()));
}
