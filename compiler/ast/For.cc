#include <string>
#include <sstream>
#include "For.h"
#include "While.h"
#include "../utilityClasses/CodeContainer.h"
#include "../utilityClasses/SymbolTable.h"
#include "../utilityClasses/CommandWrapper.h"

using std::endl;

std::string For::explain(int ind)
{
  std::stringstream expl;
  expl << indent(ind) << "for" << endl;
  expl << indent(ind) << "-init:" << endl;
  expl << init->explain(ind + 1);
  expl << indent(ind) << "-condition:" << endl;
  expl << condition->explain(ind + 1);
  expl << indent(ind) << "-update:" << endl;
  expl << update->explain(ind + 1);
  expl << indent(ind) << "-body:" << endl;
  expl << update->explain(ind + 1);
  return expl.str();
}

void For::generate(CodeContainer* code, SymbolTable* table)
{
	code->addComment("=== For:");
	// generate init statement
	init->generate(code, table);
	
	// express remainder as While
	// add update statement to loop body
	CommandWrapper wrapper(body, this);
	While temp(getLine(), condition, &wrapper);
	temp.generate(code, table);
	code->addComment("=== /For");
}

// add call to update statement to loop body
void For::genEpilogue(CodeContainer* code, SymbolTable* table)
{
	code->addComment("=== For: update");
	update->generate(code, table);
	code->addComment("=== For: /update");
}
