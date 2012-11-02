#include <stdio.h>
#include "simple_c.tab.h"

int yyerror(char* msg)
{
  printf("line %d: %s\n", yylloc.first_line, msg);
}

int main(int argc, char** argv)
{
  yyparse();
  return 0;
}
