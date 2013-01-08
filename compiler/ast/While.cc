#include <string>
#include <sstream>
#include "While.h"
#include "If.h"
#include "../utilityClasses/CommandWrapper.h"

using namespace std;

string While::explain(int ind)
{
	stringstream expl;
	expl << indent(ind) << "while, condition:" << endl;
	expl << condition->explain(ind+1);
	expl << indent(ind) << "-body:" << endl;
	expl << body->explain(ind + 1);
	return expl.str();
}

void While::generate(CodeContainer* code, SymbolTable* table)
{
	// get address of first loop instruction
	pcBeginLoop = code->address();
	// allocate memory for jump address
	beginLoopAddr = code->allocate();
	
	// add GOTO pcBeginLoop to loop body (see genEpilogue(..) below)
	CommandWrapper wrapper(body, this);
	
	// test loop condition with implicit If and use extended loop body
	If temp(getLine(), condition, &wrapper);
	temp.generate(code, table);
	
}

// callback function to CommandWrapper, adds GOTO *beginLoopAddr
void While::genEpilogue(CodeContainer* code, SymbolTable* table)
{
	code->addLoad(beginLoopAddr);
	code->push_back(0);
	code->initStatic(beginLoopAddr, code->address() - pcBeginLoop - (unsigned short) 1);
}
