%{
#include <stdio.h>
#include <string>
extern "C" void yyerror (char *s);
#include "parser.tab.h"
%}

ws 			[ \t]+
letter 		[A-Za-z]
digit 		[0-9]
name 		({letter}|_)({letter}|{digit}|_)*
number 		{digit}+
real 		({digit}*(\.{digit}+))|({digit}+(\.{digit}*))
meta 		[,;(){}:?]
arithop		[+\-*\/]
%%
{ws} 		{/*no action, no return*/}
"//".*		{/*no action, no return*/}

"void"		{store_token_name("VOID",yytext,yylineno); return VOID;}
"int" 		{store_token_name("INTEGER",yytext,yylineno); return INTEGER;}
"float" 	{store_token_name("FLOAT",yytext,yylineno); return FLOAT;}

"print"		{store_token_name("PRINT",yytext,yylineno); return PRINT;}

"return"	{store_token_name("RETURN",yytext,yylineno); return RETURN;}
"if" 		{store_token_name("IF",yytext,yylineno); return IF;}
"else" 		{store_token_name("ELSE",yytext,yylineno); return ELSE;}

"do" 		{store_token_name("DO",yytext,yylineno); return DO;}
"while" 	{store_token_name("WHILE",yytext,yylineno); return WHILE;}

"<" 		{store_token_name("LESS_THAN",yytext,yylineno); return LESS_THAN;}
"<=" 		{store_token_name("LESS_THAN_EQUAL",yytext,yylineno); return LESS_THAN_EQUAL;}
">" 		{store_token_name("GREATER_THAN",yytext,yylineno); return GREATER_THAN;}
">=" 		{store_token_name("GREATER_THAN_EQUAL",yytext,yylineno); return GREATER_THAN_EQUAL;}
"==" 		{store_token_name("EQUAL",yytext,yylineno); return EQUAL;}
"!=" 		{store_token_name("NOT_EQUAL",yytext,yylineno); return NOT_EQUAL;}

"&&" 		{store_token_name("AND",yytext,yylineno); return AND;}
"||" 		{store_token_name("OR",yytext,yylineno); return OR;}
"!" 		{store_token_name("NOT",yytext,yylineno); return NOT;}

"="			{store_token_name("ASSIGN_OP",yytext,yylineno); return ASSIGN;}

{arithop}	{store_token_name("ARITHOP",yytext,yylineno); return yytext[0];}

{name}		{std::string * str = new std::string(); *str = yytext; yylval.string_value = str;
				store_token_name("NAME",yytext,yylineno); return NAME;}
{number} 	{yylval.integer_value=atoi(yytext);	
				store_token_name("NUM",yytext,yylineno); return INTEGER_NUMBER;}
{real} 		{yylval.double_value=atof(yytext);	
				store_token_name("FNUM",yytext,yylineno); return DOUBLE_NUMBER;}
{meta} 		{store_token_name("META CHAR",yytext,yylineno); return yytext[0];}
.			{
				char err[100];
				sprintf(err, "cs316: Error: Line: %d: Scanner error", yylineno); 
				yyerror(err);
				exit(-1);
			}
\n 			{/*no action, no return*/}
%%