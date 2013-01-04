#include <string>
#include <sstream>
#include "Assignment.h"

using std::endl;

std::string Assignment::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Assignment:" << endl;
  expl << indent(ind) << "-expression:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-to NAME:" << endl;
  expl << indent(ind + 1) << name_ << endl;
  return expl.str();
}

