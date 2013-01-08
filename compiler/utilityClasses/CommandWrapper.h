#ifndef COMMANDWRAPPER_H
#define COMMANDWRAPPER_H

#include "../ast/Command.h"
#include "SymbolTable.h"

class WrapperCallback
{
	public:
		// generate code before command
		virtual void genPrologue(CodeContainer*, SymbolTable*) { }
		// generate code after command
		virtual void genEpilogue(CodeContainer*, SymbolTable*) { }
		virtual ~WrapperCallback() { }
};

/*
 * this class wraps a command, adding instructions
 * before and/or after it
 */
class CommandWrapper : public Command
{
	Command* command;
	WrapperCallback* callback;
	
	public:
		CommandWrapper(Command* command, WrapperCallback* callback) : Command(command->getLine()),
			command(command), callback(callback) { }
		void generate(CodeContainer*, SymbolTable*);
};

#endif
