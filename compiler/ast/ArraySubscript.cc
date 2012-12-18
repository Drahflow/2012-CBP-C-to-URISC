#include <string>
#include <sstream>
#include "ArraySubscript.h"

using std::endl;

std::string ArraySubscript::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "ArraySubscript:" << endl;
  expl << indent(ind) << "-position:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-from Array NAME:" << endl;
  expl << name_;
  return expl.str();
}

