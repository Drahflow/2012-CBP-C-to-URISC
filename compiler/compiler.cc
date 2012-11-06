#include <iostream>
#include "simple_c.tab.hh"

using std::cout;
using std::endl;

// root of AST, declared in simple_c.y
extern Program* parser_result;

int yyparse();

int yyerror(char* msg)
{
  cout << "line " << yylloc.first_line << ": " << msg << endl;
}



int main(int argc, char** argv)
{
  if(yyparse())
  {
    cout << "parsing error occured, aborting" << endl;
    return 1;
  }
  cout << parser_result->explain() << endl;
  return 0;
}
