#include <string>
#include <sstream>
#include <iostream>

#include "Type.h"
#include "FunctionDef.h"

using std::stringstream;
using std::endl;

typedef std::vector<VariableDef *> varlist;

std::string FunctionDef::explain(int ind) { 
  stringstream expl;
  expl << indent(ind) << "function_def:" << getLine(); 
  expl << " " << name << "," << type_name(type) << endl;
  for(varlist::const_iterator i = parameters->begin(); i != parameters->end(); ++i) {
    expl << (*i)->explain(ind + 2);
  }
  expl << block->explain(ind + 1);
  return expl.str();
}

void FunctionDef::generate(CodeContainer *code, SymbolTable *symbols) {
  code->addComment("=== Function: " + name + " ===");

  SymbolTable *localScope = symbols->createSubscope();

  // TODO: maybe just leave the parameters on the stack
  int addr = 0;
  for(varlist::const_iterator i = parameters->begin(); i != parameters->end(); ++i) {
    (*i)->setLocalAddr(addr++);
    (*i)->generate(code, localScope);
  }
  localScope->addVariable(" stackOffset", addr, false);

  block->generate(code, localScope);
}
