#include <string>
#include <sstream>
#include "And.h"
#include "FunctionCall.h"
#include "ExpressionName.h"

using std::endl;

std::string And::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "And:" << endl;
  expl << indent(ind) << "-augend:" << endl;
  expl << augend->explain(ind + 1);
  expl << indent(ind) << "-addend:" << endl;
  expl << addend->explain(ind + 1);
  return expl.str();
}

void And::generate(CodeContainer * code, SymbolTable* symbols )
{
	std::vector<Expression*>* values;
	values->push_back( augend);
	values->push_back( addend);
	Expression *functionCall = new FunctionCall(0, "And", values);
	functionCall->generate( code, symbols );

}
