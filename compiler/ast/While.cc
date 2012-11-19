#include <string>
#include <sstream>
#include "While.h"

using std::endl;

std::string While::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "while, condition:" << endl;
  expl << condition->explain(ind+1);
  expl << indent(ind) << "-body:" << endl;
  expl << body->explain(ind + 1);
  return expl.str();
}
