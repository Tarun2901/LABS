%{
    #include <stdarg.h>
    #include <stdio.h>
    #include "shared_values.h"
    #define YYSTYPE char *
    extern int yylineno;
    int yylex();
    void yyerror(const char *s);
    int yydebug = 1;
    int indent = 0;
    char *iden_dum;
%}

%token START_OF_COMMENT
%token END_OF_COMMENT
%token HEADER
%token INT
%token VOID
%token PLUS
%token EQUALS
%token ASSIGNMENT
%token EOL
%token COMMA
%token LEFT_PARANTHESIS
%token RIGHT_PARANTHESIS
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token ID
%token NUM

%%
program: S | HEADER S ;
S: S A | A;
A: var_dec | func;
var_dec: type ID EOL;
type: INT | VOID;
func: type ID LEFT_BRACKET params RIGHT_BRACKET compound_stmt;
params: param_list | VOID;
param_list: param_list COMMA param | param;
param: type ID;
compound_stmt: LEFT_PARANTHESIS local statement_list RIGHT_PARANTHESIS;
local: local var_dec | %empty;
statement_list: statement_list statement | %empty;
statement: expression_stmt | compound_stmt;
expression_stmt: E EOL | EOL;
E: var ASSIGNMENT E | simple_expression;
var: ID;
simple_expression: Add_EXP;
Add_EXP: Add_EXP PLUS factor | factor;
factor: LEFT_BRACKET E RIGHT_BRACKET | var | call | NUM;
call: ID LEFT_BRACKET args RIGHT_BRACKET;
args: arg_list | %empty;
arg_list: arg_list COMMA E | E;

%%                                                                              
int main (void) {     
   extern FILE *yyin; 
   yyin = fopen("testfile_two.c", "r"); 
   yyparse ();{printf("Parsed Successfully\n");}
}