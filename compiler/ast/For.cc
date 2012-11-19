#include <string>
#include <sstream>
#include "For.h"

using std::endl;

std::string For::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "for" << endl;
  expl << indent(ind) << "-init:" << endl;
  expl << init->explain(ind + 1);
  expl << indent(ind) << "-condition:" << endl;
  expl << condition->explain(ind + 1);
  expl << indent(ind) << "-update:" << endl;
  expl << update->explain(ind + 1);
  expl << indent(ind) << "-body:" << endl;
  expl << update->explain(ind + 1);
  return expl.str();
}
