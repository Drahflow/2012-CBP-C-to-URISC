#include <string>
#include <sstream>
#include "Return.h"

using std::endl;

std::string Return::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "return, value:" << endl;
  expl << value->explain(ind + 1);
  return expl.str();
}
