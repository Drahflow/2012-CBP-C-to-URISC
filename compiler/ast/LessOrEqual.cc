#include <string>
#include <sstream>
#include "LessOrEqual.h"

using std::endl;

std::string LessOrEqual::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "LessOrEqual:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

