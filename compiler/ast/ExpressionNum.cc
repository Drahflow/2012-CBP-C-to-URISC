#include <string>
#include <sstream>
#include "ExpressionNum.h"

using std::endl;

std::string ExpressionNum::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "ExpressionNum:" << endl;
  expl << indent(ind) << num_ << endl;
  return expl.str();
}

