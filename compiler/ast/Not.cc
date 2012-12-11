#include <string>
#include <sstream>
#include "Not.h"

using std::endl;

std::string Not::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Not:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  return expl.str();
}

