#include "CommandWrapper.h"

void CommandWrapper::generate(CodeContainer* code, SymbolTable* table)
{
	callback->genPrologue(code, table);
	command->generate(code, table);
	callback->genEpilogue(code, table);
}

