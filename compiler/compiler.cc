#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <libgen.h>
#include <string.h>
#include <malloc.h>
#include "simple_c.tab.hh"
#include "utilityClasses/CodeContainer.h"
#include "utilityClasses/SymbolTable.h"

#define DEFAULT_OUTPUT_EXTENSION ".urisc"

using namespace std;

// root of AST, declared in simple_c.y
extern Program* parser_result;

int yyparse();

void yyerror(const char* msg)
{
	cerr << "line " << yylloc.first_line << ": " << msg << endl;
}

void print_usage(const char* executable)
{
	cerr << "usage: " << executable << " [-o BINARY] SOURCE" << endl;
}

void print_file_error(const string& filename)
{
	cerr << "unable to open file: " << filename << endl;
}

int main(int argc, char** argv)
{	
	string inputName;
	string outputName;
	if(argc < 2 || argc > 4)
	{
		print_usage(argv[0]);
		return 1;
	}
	
	// parse arguments
	for(int i = 1; i < argc; i++)
	{
		string arg(argv[i]);
		if(arg == "-o")
		{
			if(!outputName.empty() || ++i >= argc)
			{
				print_usage(argv[0]);
				return 1;
			}
			outputName = argv[i];
		}
		else
		{
			if(!inputName.empty())
			{
				print_usage(argv[0]);
				return 1;
			}
			inputName = arg;
		}
	}
	
	// generate output file name, if none specified
	// (i.e., replace extension and use working directory)
	if(outputName.empty())
	{
		char* _inputName = strdup(inputName.c_str());
		string inputBasename = basename(_inputName);
		free(_inputName);
		size_t index = inputBasename.rfind(".");
		if(index == string::npos)
			outputName = inputBasename;
		else
			outputName = inputBasename.substr(0, index);
		outputName.append(DEFAULT_OUTPUT_EXTENSION);
	}
	
	// cout << "input: " << inputName << "; output: " << outputName << endl;
	
	// open input file
	extern FILE* yyin;
	
	yyin = fopen(inputName.c_str(), "r");
	if(yyin == NULL)
	{
		print_file_error(inputName);
		return 1;	
	}
	
	if(yyparse())
	{
		fclose(yyin);
		cerr << "parsing error occurred, aborting" << endl;
		return 1;
	}
	fclose(yyin);
	
	cout << parser_result->explain() << endl;
	SymbolTable *symbolTable = new SymbolTable;
	CodeContainer *codeContainer = new CodeContainer;
	parser_result->codeGeneration1(codeContainer, symbolTable);
	parser_result->codeGeneration2(codeContainer, symbolTable);
	
	// open output file
	ofstream out(outputName.c_str());
	if(!out.is_open())
	{
		print_file_error(outputName);
		return 1;
	}
	string codeString = codeContainer->getCodeString();
	out << codeString;
	if(!out.good())
	{
		cerr << "error while writing to file: " << outputName << endl;
		return 1;
	}
	return 0;
}
