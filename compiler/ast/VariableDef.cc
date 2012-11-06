#include <string>
#include <sstream>
#include "Type.h"
#include "VariableDef.h"

using std::stringstream;

std::string VariableDef::explain()
{ 
  stringstream expl;
  expl << "variable_def:" << getLine(); 
  expl << " " << name << "," << type_name(type) << " /";
  return expl.str();
}
