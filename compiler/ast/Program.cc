#include <string>
#include <sstream>
#include <vector>

#include "Program.h"

using std::stringstream;
using std::vector;
using std::endl;

std::string Program::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "program:" << getLine() << endl;

  vector<Node*>::iterator it;
  for(it = definitions.begin(); it < definitions.end(); it++)
  {
    expl << (*it)->explain(ind + 1);
  }
  return expl.str();
}

void Program::codeGeneration1(CodeContainer *code, SymbolTable *symbols) {
  code->addComment("===== program starts here =====");
  code->addComment("===== initial jump to main =====");
  int jumpDelta = code->allocate();
  code->addLoad(jumpDelta);
  code->push_back(0);
  int afterJumpAddr = code->address();

  for(vector<Node *>::const_iterator i = definitions.begin(); i != definitions.end(); ++i) {
    (*i)->generate(code, symbols);
  }

  code->initStatic(jumpDelta, afterJumpAddr - symbols->resolveVariable("main").addr - 1);
}

void Program::codeGeneration2(CodeContainer *, SymbolTable *) {
}
