#include <string>
#include <sstream>
#include "Type.h"
#include "VariableDef.h"

using std::stringstream;
using std::endl;

std::string VariableDef::explain(int ind)
{ 
  stringstream expl;
  expl << indent(ind) << "variable_def:" << getLine(); 
  expl << " " << name << "," << type_name(type) << endl;
  return expl.str();
}

void VariableDef::setLocalAddr(int a) {
  if(global) throw std::logic_error("Local addr set for global variable");
  addr = a;
}

void VariableDef::generate(CodeContainer *code, SymbolTable *symbols) {
  if(global) {
    addr = code->allocate();
  } else if(addr == 0xFFFF) {
    throw std::logic_error("code generation of unplaced local variable");
  }

  symbols->addVariable(getName(), addr, global);
}
