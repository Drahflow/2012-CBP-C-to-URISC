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
  std::vector<VariableDef*>*    var_def_list;
  Command*			command;
  Type				type;
  Expression*			expression;
  std::vector<Expression*>*		values;
  FunctionDef*          function_def;
  Block*                block;
}

%{
  // AST root is stored here
  Program* parser_result = NULL;
%}

%type <prog> program;
%type <var_def> global_variable_definition variable_definition parameter
%type <var_def_list> variable_definitions parameter_list parameters
%type <int_list> var_init_list
%type <type> type_definition
%type <command_list> commands
%type <command> command
%type <expression> ifclause
%type <expression> expression
%type <block> block
%type <function_def> function_definition
%type <values> values;

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
  | program function_definition {  $1->add($2); $$ = $1; }
  | global_variable_definition { $$ = new Program(@1.first_line); $$->add($1); parser_result = $$; }
  | function_definition {  $$ = new Program(@1.first_line);  $$->add($1); parser_result = $$; };

global_variable_definition: variable_definition {($1)->setGlobal(); $$ = $1; }
  | type_definition NAME '=' '{' var_init_list '}' ';'
    { 
      IntArrayDef* a = new IntArrayDef(@$.first_line, $2);
      a->setGlobal();
      a->initialize(*($5));
      delete $5;
      $$ = a;
    }
  | type_definition NAME '[' NUM ']' '=' '{' var_init_list '}' ';'
    {
      IntArrayDef* a = new IntArrayDef(@$.first_line, $2, $4);
      a->setGlobal();
      a->initialize(*($8));
      delete $8;
      $$ = a; 
    };

var_init_list: var_init_list ',' NUM { $$ = $1; $1->push_back($3); }
  | NUM { $$ = new std::vector<int>(); $$->push_back($1); };

variable_definition:
  type_definition NAME ';' { $$ = new VariableDef(@$.first_line, $1, $2); };

function_definition:
  type_definition NAME '(' parameter_list ')' block { $$ = new FunctionDef(@$.first_line, $1, $2, $4, $6); };

// function_type_definition: VOID | INT;

type_definition: INT { $$ = TYPE_INT; };

parameter_list: VOID { $$ = new std::vector<VariableDef *>(); }
              | parameters { $$ = $1; }
              ;

parameters: parameter { $$ = new std::vector<VariableDef *>(); $$->push_back($1); }
          | parameters ',' parameter { $1->push_back($3); $$ = $1; }
          ;
  
parameter: type_definition NAME { $$ = new VariableDef(@$.first_line, $1, $2); }
         ;

block: ';' { $$ = new Block(@$.first_line); } 
  | '{' variable_definitions commands '}' { $$ = new Block(@$.first_line, $3, $2); } 
  | '{' commands '}' { $$ = new Block(@$.first_line, $2); }
  | '{' '}' { $$ = new Block(@$.first_line); }
  ;

variable_definitions: variable_definitions variable_definition { $1->push_back($2); $$ = $1; }
  | variable_definition { $$ = new std::vector<VariableDef *>(); $$->push_back($1); }
  ;

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
    NAME '=' expression       { $$ = new Assignment(@$.first_line,$1,$3);}
  | NAME '(' values ')'       { $$ = new FunctionCall(@$.first_line,$1,$3);}
  | '*' expression '=' expression{$$=new IndirectionAssignment(@$.first_line,$2,$4);}
  | expression '+' expression { $$ = new Addition(@$.first_line, $1,$3);}
  | expression '-' expression { $$ = new Subtraction(@$.first_line, $1, $3);}
  | expression '*' expression { $$ = new Multiplication(@$.first_line, $1, $3);}
  | expression '/' expression { $$ = new Division(@$.first_line, $1, $3);}
  | expression '&' expression { $$ = new And(@$.first_line, $1, $3);} 
  | expression '|' expression { $$ = new Or(@$.first_line, $1, $3);} 
  | expression EQ expression  { $$ = new Equal(@$.first_line, $1, $3);}
  | expression NE expression  { $$ = new NotEqual(@$.first_line, $1, $3);}
  | expression '<' expression { $$ = new Less(@$.first_line, $1, $3);}
  | expression '>' expression { $$ = new Greater(@$.first_line, $1, $3);}
  | expression LTEQ expression{ $$ = new LessOrEqual(@$.first_line, $1, $3);}
  | expression GTEQ expression{ $$ = new GreaterOrEqual(@$.first_line, $1, $3);}
  | '(' expression ')'        { $$ = $2;}
  | '!' expression            { $$ = new Not(@$.first_line, $2);}
  | NAME                      { $$ = new ExpressionName(@$.first_line,$1);}
  | NAME '[' expression ']'   {
    $$ = new Indirection(@$.first_line, new Addition(@$.first_line, new ExpressionName(@$.first_line, $1), $3));
  }
  | '*' expression            { $$ = new Indirection(@$.first_line,$2);}
  | NUM                       { $$ = new ExpressionNum(@$.first_line,$1);}
  | '-' NUM                   { $$ = new ExpressionNum(@$.first_line, -$2); }
  ;

values: { $$ = new std::vector<Expression *>(); } 
  | values ',' expression { $$ = $1; $1->push_back($3); }
  | expression            { $$ = new std::vector<Expression*>(); $$->push_back($1);}
  ;
