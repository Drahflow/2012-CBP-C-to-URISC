#include <stdio.h>

int yyerror(char* msg)
{
  printf("%s\n", msg);
}

int main(int argc, char** argv)
{
  yyparse();
  return 0;
}
