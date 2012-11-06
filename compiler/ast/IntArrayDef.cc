#include <string>
#include <sstream>
#include "IntArrayDef.h"

using std::stringstream;

std::string IntArrayDef::explain()
{
  stringstream expl;
  expl << "int_array_def:" << getLine() << " " << getName();
  expl << " size=" << size << " " << "#data=" << data.size() << " /";
  return expl.str();
}
