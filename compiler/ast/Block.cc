#include "Block.h"

#include <sstream>

using namespace std;

template<class S, class C> static void explainSubitems(S &s, int ind, const C &c) {
  for(typename C::const_iterator i = c.begin(); i != c.end(); ++i) s << (*i)->explain(ind);
}

string Block::explain(int ind) {
  stringstream expl;
  expl << indent(ind) << "block:" << getLine() << endl;
  if(variables) explainSubitems(expl, ind + 1, *variables);
  if(commands) explainSubitems(expl, ind + 1, *commands);
  return expl.str();
}

typedef std::vector<VariableDef *> varlist;

void Block::generate(CodeContainer *code, SymbolTable *symbols) {
  SymbolTable *localScope = symbols->createSubscope();

  if(variables) {
    int addr = localScope->resolveVariable(" stackOffset").addr;
    for(varlist::const_iterator i = variables->begin(); i != variables->end(); ++i) {
      (*i)->setLocalAddr(addr++);
      (*i)->generate(code, localScope);
    }
    localScope->addVariable(" stackOffset", addr, false);
  }

  for(vector<Command *>::const_iterator i = commands->begin(); i != commands->end(); ++i) {
    // code->addComment((*i)->explain(0)); // does not work in reality, because of \n
    (*i)->generate(code, localScope);
  }
}
