#include <string>
#include <sstream>
#include "And.h"

using std::endl;

std::string And::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "And:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

