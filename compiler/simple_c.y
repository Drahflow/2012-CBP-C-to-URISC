%{
  #define YYERROR_VERBOSE
%}

%locations

%union {
  char	*name;
  int	num;
}

%token <num> NUM
%token <name> NAME
%token INT
%token VOID	
%token ELSE
%token WHILE
%token RETURN
%token FOR
%token IF
%token GTEQ
%token LTEQ
%token EQ
%token NE

%start program

%%

program: program global_variable_definition
  | program function_definition
  | global_variable_definition
  | function_definition;

global_variable_definition: variable_definition
  | type_definition NAME '=' '{' var_init_list '}' ';'
  | type_definition NAME '[' NUM ']' '=' '{' var_init_list '}' ';';

var_init_list: var_init_list ',' NUM
  | NUM;

variable_definition: type_definition NAME ';';

function_definition: type_definition NAME '(' parameter_list ')' block;

// function_type_definition: VOID | INT;

type_definition: INT;

parameter_list: VOID
  | parameters;

parameters: parameter
  | parameters ',' parameter;
  
parameter: type_definition NAME;

block: ';'
  | '{' variable_definitions commands '}'
  | '{' commands '}'
  | '{' '}'
  ;

variable_definitions: variable_definitions variable_definition
  | variable_definition;

commands: commands command
  | command;

command: block
  | expression ';'
  | ifclause command
  | ifclause command ELSE command
  | WHILE '(' expression ')' command
  | RETURN expression ';'
  | FOR '(' expression ';' expression ';' expression ')' command;

ifclause: IF '(' expression ')';

expression: NAME '=' expression
  | NAME '(' values ')'
  | '*' expression '=' expression
  | expression '+' expression
  | expression '-' expression
  | expression '*' expression
  | expression '/' expression
  | expression '&' expression
  | expression '|' expression
  | expression EQ expression
  | expression NE expression
  | expression '<' expression
  | expression '>' expression
  | expression LTEQ expression
  | expression GTEQ expression
  | '(' expression ')'
  | '!' expression
  | NAME
  | NAME '[' expression ']'
  | '*' expression
  | NUM
  | '-' NUM;

values: /* no function arguments */
  | values ',' expression
  | expression
