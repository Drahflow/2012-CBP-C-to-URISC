#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include "Node.h"
#include "FunctionDef.h"
#include "../utilityClasses/CodeContainer.h"
#include "../utilityClasses/SymbolTable.h"

class Program : public Node
{
	std::vector<Node*> definitions;
	public:
		Program(int line) : Node(line) { };
		void add(VariableDef* def) { definitions.push_back(def); }
		void add(FunctionDef* def) { definitions.push_back(def); }
		void codeGeneration1(CodeContainer *codeContainer, SymbolTable *symbolTable);
		void codeGeneration2(CodeContainer *codeContainer, SymbolTable *symbolTable);
		void generate(CodeContainer* code, SymbolTable* table) { codeGeneration1(code, table); }
		std::string explain(int ind = 0);
};

#endif
