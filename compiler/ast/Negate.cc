#include <string>
#include <sstream>
#include "Negate.h"

using std::endl;

std::string Negate::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Negate:" << endl;
  expl << indent(ind) << "-" << neg_ << endl;
  return expl.str();
}

