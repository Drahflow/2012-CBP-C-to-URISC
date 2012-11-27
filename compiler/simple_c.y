%code requires {
 #include "ast.h"
}

%{
  #define YYERROR_VERBOSE
  
  void yyerror(const char* msg);
  int yylex(); 
%}

%locations

%union {
  // tokens with values
  char*	name;
  int	num;
  
  // non-terminals
  Program*			prog;
  VariableDef*			var_def;
  std::vector<int>*		int_list;
  std::vector<Command*>*	command_list;
  Command*			command;
  Type				type;
  Expression*			expression;
  FunctionDef*          function_def;
}

%{
  // AST root is stored here
  Program* parser_result = NULL;
%}

%type <prog> program;
%type <var_def> global_variable_definition variable_definition 
%type <int_list> var_init_list
%type <type> type_definition
%type <command_list> commands
%type <command> command
%type <expression> ifclause
%type <expression> expression
%type <command> block
%type <function_def> function_definition

%destructor { delete $$; } <int_list>
%destructor { delete $$; } <command_list>
%destructor { free($$); } <name>

%token <num> NUM
%token <name> NAME
%token INT
%token VOID	
%token ELSE
%token WHILE
%token RETURN
%token FOR
%token IF
// %token GTEQ
// %token LTEQ
// %token EQ
// %token NE

%left '<' '>' GTEQ LTEQ EQ NE
%left '+' '-'
%left '*' '/'
%left '&' '|'
%left '!'
%right '='

%start program

%%

program: program global_variable_definition { $1->add($2); $$ = $1; }
  | program function_definition { /* $1->add($2); $$ = $1; */ }
  | global_variable_definition { $$ = new Program(@1.first_line); $$->add($1); parser_result = $$; }
  | function_definition {  $$ = new Program(@1.first_line); /* $$->add($1); */ parser_result = $$; };

global_variable_definition: variable_definition { $$ = $1; }
  | type_definition NAME '=' '{' var_init_list '}' ';'
    { 
      IntArrayDef* a = new IntArrayDef(@$.first_line, $2);
      a->initialize(*($5));
      delete $5;
      $$ = a;
    }
  | type_definition NAME '[' NUM ']' '=' '{' var_init_list '}' ';'
    {
      IntArrayDef* a = new IntArrayDef(@$.first_line, $2, $4);
      a->initialize(*($8));
      delete $8;
      $$ = a; 
    };

var_init_list: var_init_list ',' NUM { $$ = $1; $1->push_back($3); }
  | NUM { $$ = new std::vector<int>(); $$->push_back($1); };

variable_definition:
  type_definition NAME ';' { $$ = new VariableDef(@$.first_line, $1, $2); };

function_definition:
  type_definition NAME '(' parameter_list ')' block { $$ = new FunctionDef(@$.first_line, $1, $2); };

// function_type_definition: VOID | INT;

type_definition: INT { $$ = TYPE_INT; };

parameter_list: VOID
  | parameters;

parameters: parameter
  | parameters ',' parameter;
  
parameter: type_definition NAME;

block: ';' { $$ = new Block(@$.first_line); } 
  | '{' variable_definitions commands '}' { /* $$ = new Block(@$.first_line, $3, $2); delete $2; delete $3; */ } 
  | '{' commands '}' { $$ = new Block(@$.first_line, *($2)); delete $2; }
  | '{' '}' { $$ = new Block(@$.first_line); }
  ;

variable_definitions: variable_definitions variable_definition
  | variable_definition;

commands: commands command { $$ = $1; $1->push_back($2);  }
  | command { $$ = new std::vector<Command*>(); $$->push_back($1); };

command: block { $$ = $1; }
  | expression ';' { $$ = $1; }
  | ifclause command { $$ = new If(@$.first_line, $1, $2); }
  | ifclause command ELSE command { $$ = new If(@$.first_line, $1, $2, $4); }
  | WHILE '(' expression ')' command { $$ = new While(@$.first_line, $3, $5); }
  | RETURN expression ';' { $$ = new Return(@$.first_line, $2); }
  | FOR '(' expression ';' expression ';' expression ')' command { $$ = new For(@$.first_line, $3, $5, $7, $9); };

ifclause: IF '(' expression ')' { $$ = $3; };

expression: 
    NAME '=' expression
  | NAME '(' values ')'
  | '*' expression '=' expression
  | expression '+' expression { $$ = new Addition(@$.first_line, $1,$3);}
  | expression '-' expression { $$ = new Subtraction(@$.first_line, $1, $3);}
  | expression '*' expression { $$ = new Multiplication(@$.first_line, $1, $3);}
  | expression '/' expression { $$ = new Division(@$.first_line, $1, $3);}
  | expression '&' expression 
  | expression '|' expression
  | expression EQ expression  
  | expression NE expression
  | expression '<' expression
  | expression '>' expression
  | expression LTEQ expression
  | expression GTEQ expression
  | '(' expression ')' {$$ = $2;}
  | '!' expression
  | NAME
  | NAME '[' expression ']'
  | '*' expression
  | NUM 
  | '-' NUM;

values: /* no function arguments */
  | values ',' expression
  | expression
