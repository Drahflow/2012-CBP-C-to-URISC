#include <string>
#include <sstream>
#include "IntArrayDef.h"

using std::stringstream;
using std::endl;

std::string IntArrayDef::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "int_array_def:" << getLine() << " " << getName();
  expl << " size=" << size << " " << "#data=" << data.size() << endl;
  return expl.str();
}
