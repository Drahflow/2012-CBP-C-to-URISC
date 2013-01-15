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
  static int instructionPointerTemp = code->allocate();

  SymbolTable *localScope = symbols->createSubscope();
  int localVariableCount = block->getLocalVariableCount();
  localScope->addVariable(" stackOffset", -localVariableCount + 1, false);

  code->addComment("=== Function: " + name + " (Return Code) ===");
  localScope->addVariable(" functionReturn", code->address(), false);

  // increment the stack pointer
  int stackIncConst = code->allocate(-localVariableCount);
  code->addLoad(stackIncConst);
  code->push_back(code->stackPointerAddr);

  // return to caller
  {
    int addr = code->address();
    int addrAddr = code->allocate(-(addr + 20));

    code->addComment("stack read for return");
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr); // clear = acc = 0
    code->push_back(addr + 18);
    code->push_back(addr + 18); // code = 0
    code->push_back(code->stackPointerAddr); // acc = expr
    code->push_back(code->clearAddr); // clear = acc = -expr
    code->push_back(code->clearAddr); // skipped (or expr == 0)
    code->push_back(addr + 18); // code = acc = expr
    code->push_back(instructionPointerTemp);
    code->push_back(instructionPointerTemp);
    code->push_back(instructionPointerTemp); // tmp = acc = 0
    code->push_back(addrAddr); // acc = -(code address)
    code->push_back(instructionPointerTemp); // tmp = code address
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr);
    code->push_back(code->clearAddr); // clear = acc = 0
    code->push_back(0xEEEE); // self modified // acc = *(original expr) = return address
    code->push_back(instructionPointerTemp); // acc = tmp - return address
    code->push_back(0); // instr = instr - acc = instr - (code address - return address)
  }

  code->addComment("=== Function: " + name + " ===");
  symbols->addVariable(name, code->address(), true);

  // decrement the stack pointer for local variables
  int stackDecConst = code->allocate(localVariableCount);
  code->addLoad(stackDecConst);
  code->push_back(code->stackPointerAddr);

  int addr = -localVariableCount - 1;
  for(varlist::const_iterator i = parameters->begin(); i != parameters->end(); ++i) {
    (*i)->setLocalAddr(--addr);
    (*i)->generate(code, localScope);
  }

  block->generate(code, localScope);

  // generate jump back to return code
  int deltaAddr = code->allocate(code->address() + 5 - localScope->resolveVariable(" functionReturn").addr);
  code->push_back(code->clearAddr);
  code->push_back(code->clearAddr);
  code->push_back(code->clearAddr);
  code->push_back(deltaAddr);
  code->push_back(0);
}
