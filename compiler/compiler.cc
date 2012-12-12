#include <iostream>
#include <string>
#include "simple_c.tab.hh"
#include "utilityClasses/CodeContainer.h"
#include "utilityClasses/SymbolTable.h"

using std::cout;
using std::endl;

// root of AST, declared in simple_c.y
extern Program* parser_result;

int yyparse();

int yyerror(const char* msg)
{
	cout << "line " << yylloc.first_line << ": " << msg << endl;
}



int main(int argc, char** argv)
{
	if(yyparse())
	{
		cout << "parsing error occured, aborting" << endl;
		return 1;
	}
	cout << parser_result->explain() << endl;
	SymbolTable *symbolTable = new SymbolTable;
	CodeContainer *codeContainer = new CodeContainer;
	parser_result->codeGeneration1(codeContainer, symbolTable);
	parser_result->codeGeneration2(codeContainer, symbolTable);
	//std::ostringstream codeString = codeContainer->getCodeString();

	std::string codeString = codeContainer->getCodeString();
	cout << codeString;
	return 0;
}
