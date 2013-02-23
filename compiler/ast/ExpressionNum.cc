#include <string>
#include <sstream>
#include "ExpressionNum.h"

using namespace std;

string ExpressionNum::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "ExpressionNum:" << endl;
  expl << indent(ind) << num << endl;
  return expl.str();
}

void ExpressionNum::generate(CodeContainer *code, SymbolTable *) {
  stringstream comment;
  comment << "constant " << num;
  code->addComment(comment.str());
  code->addNOP();
  if(num == 0) {
    code->push_back(code->exprResultAddr);
    code->push_back(code->exprResultAddr);
    code->push_back(code->exprResultAddr);
    code->push_back(code->exprResultAddr); // expr = 0
  } else {
    int addr = code->allocate();
    code->initStatic(addr, -num);
    code->push_back(code->exprResultAddr);
    code->push_back(code->exprResultAddr);
    code->push_back(code->exprResultAddr); // expr = 0
    code->push_back(addr); // acc = -num
    code->push_back(code->exprResultAddr); // expr = num
    code->push_back(code->clearAddr); // skipped
  }
}
