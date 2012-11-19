#include <string>
#include <sstream>
#include "If.h"

using std::endl;

std::string If::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "if, condition:" << endl;
  expl << condition->explain(ind + 1);
  expl << indent(ind) << "-then:" << endl;
  expl << thenBranch->explain(ind + 1);
  if(elseBranch == NULL)
    expl << endl << indent(ind) << "-else:" << endl << elseBranch->explain(ind + 1);
  return expl.str();
}
