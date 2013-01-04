#include <string>
#include <sstream>
#include "Type.h"
#include "FunctionDef.h"

using std::stringstream;
using std::endl;

std::string FunctionDef::explain(int ind)
{ 
  typedef std::vector<VariableDef *> varlist;

  stringstream expl;
  expl << indent(ind) << "function_def:" << getLine(); 
  expl << " " << name << "," << type_name(type) << endl;
  for(varlist::const_iterator i = parameters->begin(); i != parameters->end(); ++i) {
    expl << (*i)->explain(ind + 2);
  }
  expl << block->explain(ind + 1);
  return expl.str();
}
