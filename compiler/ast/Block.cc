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
