#include <string>
#include <sstream>
#include "IndirectionAssignment.h"

using std::endl;

std::string IndirectionAssignment::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "Assignment:" << endl;
  expl << indent(ind) << "-expression:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-to pointer adress:" << endl;
  expl << pointer_->explain(ind + 1);;
  return expl.str();
}

