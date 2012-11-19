#include <string>
#include <sstream>
#include <vector>
#include "Program.h"

using std::stringstream;
using std::vector;
using std::endl;

std::string Program::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "program:" << getLine() << endl;

  vector<Node*>::iterator it;
  for(it = definitions.begin(); it < definitions.end(); it++)
  {
    expl << (*it)->explain(ind + 1);
  }
  return expl.str();
}
