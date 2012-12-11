#include <string>
#include <sstream>
#include "Subtraction.h"

using std::endl;

std::string Subtraction::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Subtraction:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

