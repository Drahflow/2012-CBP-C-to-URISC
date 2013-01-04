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

void Program::codeGeneration1(CodeContainer *codeContainer, SymbolTable *symbolTable) {
  codeContainer->addComment("===== program starts here =====");
  codeContainer->addClearAkk();

  for(vector<Node *>::const_iterator i = definitions.begin(); i != definitions.end(); ++i) {
    (*i)->generate(codeContainer, symbolTable);
  }
}

void Program::codeGeneration2(CodeContainer *codeContainer, SymbolTable *symbolTable) {
}
