#include <string>
#include <sstream>
#include "Indirection.h"

using std::endl;

std::string Indirection::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Indirection:" << endl;
  expl << indent(ind) << "-expression:" << endl;
  expl << augend->explain(ind + 1);
  return expl.str();
}

