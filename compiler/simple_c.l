%option noyywrap
%{
  #include <stdio.h>
  #include <string.h>
  #include "simple_c.tab.h"
%}

DIGIT	[0-9]
LETTER	[a-zA-Z]

NAME	{LETTER}({LETTER}|{DIGIT})*
INT_NUM {DIGIT}+

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
{INT}		{ return INT; }
{VOID}		{ return VOID; }
{ELSE}		{ return ELSE; }
{WHILE}		{ return WHILE; }
{RETURN}	{ return RETURN; }
{FOR}		{ return FOR; }
{IF}		{ return IF; }
{GTEQ}		{ return GTEQ; }
{LTEQ}		{ return LTEQ; }
{EQ}		{ return EQ; }
{NE}		{ return NE; }

{INT_NUM}	{ yylval.num = atoi(yytext); }
{NAME}		{ yylval.name = strdup(yytext); }
[[:blank:]]+	{ }
.		{ return yytext[0]; }
%%
