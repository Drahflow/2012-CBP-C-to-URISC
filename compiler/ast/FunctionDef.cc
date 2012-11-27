#include <string>
#include <sstream>
#include "Type.h"
#include "FunctionDef.h"

using std::stringstream;
using std::endl;

std::string FunctionDef::explain(int ind)
{ 
  stringstream expl;
  expl << indent(ind) << "function_def:" << getLine(); 
  expl << " " << name << "," << type_name(type) << endl;
  return expl.str();
}
