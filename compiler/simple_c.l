%option noyywrap yylineno
%x COMMENT SHORT_COMMENT
%{
  #include <stdio.h>
  #include <string.h>
  #include "simple_c.tab.hh"
  #define YY_USER_ACTION yylloc.first_line = yylineno;
  
%}



DIGIT			[0-9]
LETTER			[a-zA-Z]
HEX_DIGIT		[0-9a-fA-F]
HEX_PREFIX		"0x"
COMMENT_BEGIN		"/*"
COMMENT_END		"*/"
SHORT_COMMENT_BEGIN	"//"
SHORT_COMMENT_END	\n


NAME	{LETTER}({LETTER}|{DIGIT})*
INT_NUM {DIGIT}+
HEX_NUM {HEX_PREFIX}{HEX_DIGIT}+

INT	int
VOID	void
ELSE	else
WHILE	while
RETURN	return
FOR	for
IF	if
GTEQ	">="
LTEQ	"<="
EQ	"=="
NE	"!="


%%
{COMMENT_BEGIN}				{ BEGIN(COMMENT); }
<COMMENT>{COMMENT_END}			{ BEGIN(INITIAL); }
{SHORT_COMMENT_BEGIN}			{ BEGIN(SHORT_COMMENT); }
<SHORT_COMMENT>{SHORT_COMMENT_END}	{ BEGIN(INITIAL); }
<SHORT_COMMENT>.			{ }
<COMMENT>(.|\n)				{ }

{INT}					{ return INT; }
{VOID}					{ return VOID; }
{ELSE}					{ return ELSE; }
{WHILE}					{ return WHILE; }
{RETURN}				{ return RETURN; }
{FOR}					{ return FOR; }
{IF}					{ return IF; }
{GTEQ}					{ return GTEQ; }
{LTEQ}					{ return LTEQ; }
{EQ}					{ return EQ; }
{NE}					{ return NE; }

{HEX_NUM}				{ sscanf(yytext, "%x", &yylval.num); return NUM; }
{INT_NUM}				{ yylval.num = atoi(yytext); return NUM; }
{NAME}					{ yylval.name = strdup(yytext); return NAME; }

[\t\r\n ]+				{ }
.					{ return yytext[0]; }
%%
