#include <string>
#include <sstream>
#include "ExpressionName.h"

using std::endl;

std::string ExpressionName::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "ExpressionName:" << endl;
  expl << indent(ind) << name_ << endl;
  return expl.str();
}

