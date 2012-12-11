#include <string>
#include <sstream>
#include "FunctionCall.h"

using std::endl;

std::string FunctionCall::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "FunctionCall:" << endl;
//  expl << indent(ind) << "-expression:" << endl;
//  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-to NAME:" << endl;
  expl << name_;
  return expl.str();
}

