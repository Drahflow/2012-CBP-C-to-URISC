#include <string>
#include <sstream>
#include <vector>
#include "Program.h"

using std::stringstream;
using std::vector;
using std::endl;

std::string Program::explain()
{
  stringstream expl;
  expl << "program:" << getLine() << endl;

  vector<Node*>::iterator it;
  for(it = definitions.begin(); it < definitions.end(); it++)
  {
    expl << (*it)->explain() << endl;
  }

  expl << "/program";
  return expl.str();
}
