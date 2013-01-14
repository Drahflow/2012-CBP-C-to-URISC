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

void VariableDef::generate(CodeContainer *code, SymbolTable *symbols) {
  int addr = code->allocate();
  symbols->addVariable(getName(), addr, global);
}
