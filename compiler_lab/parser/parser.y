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
%token IF
%token ELSE
%token INT
%token RETURN
%token VOID
%token WHILE
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token LESS_THAN
%token LESS_OR_EQUAL
%token GREATER_THAN
%token GREATER_OR_EQUAL
%token EQUALS
%token ASSIGNMENT
%token NOT_EQUALS
%token EOL
%token COMMA
%token LEFT_PARANTHESIS
%token RIGHT_PARANTHESIS
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_SQR_BRACKET
%token RIGHT_SQR_BRACKET
%token ID
%token NUM

%%
program: declaration_list | HEADER declaration_list ;
declaration_list: declaration_list declaration | declaration;
declaration: var_declaration | fun_declaration;
var_declaration: type_specifier ID EOL | type_specifier ID LEFT_SQR_BRACKET NUM RIGHT_SQR_BRACKET EOL;
type_specifier: INT | VOID;
fun_declaration: type_specifier ID LEFT_BRACKET params RIGHT_BRACKET compound_stmt;
params: param_list | VOID;
param_list: param_list COMMA param | param;
param: type_specifier ID | type_specifier ID LEFT_SQR_BRACKET RIGHT_SQR_BRACKET;
compound_stmt: LEFT_PARANTHESIS local_declarations statement_list RIGHT_PARANTHESIS;
local_declarations: local_declarations var_declaration | %empty;
statement_list: statement_list statement | %empty;
statement: expression_stmt | compound_stmt | selection_stmt | iteration_stmt |
return_stmt;
expression_stmt: expression EOL | EOL;
selection_stmt: IF LEFT_BRACKET expression RIGHT_BRACKET statement | IF LEFT_BRACKET expression RIGHT_BRACKET statement ELSE
statement;
iteration_stmt: WHILE LEFT_BRACKET expression RIGHT_BRACKET statement;
return_stmt: RETURN EOL | RETURN expression EOL;
expression: var ASSIGNMENT expression | simple_expression;
var: ID | ID LEFT_SQR_BRACKET expression RIGHT_SQR_BRACKET;
simple_expression: additive_expression relop additive_expression | additive_expression;
relop: LESS_THAN | LESS_OR_EQUAL | GREATER_THAN | GREATER_OR_EQUAL | EQUALS | NOT_EQUALS;
additive_expression: additive_expression addop term | term;
addop: PLUS | MINUS;
term: term mulop factor | factor;
mulop: MULTIPLY | DIVIDE;
factor: LEFT_BRACKET expression RIGHT_BRACKET | var | call | NUM;
call: ID LEFT_BRACKET args RIGHT_BRACKET;
args: arg_list | %empty;
arg_list: arg_list COMMA expression | expression;

%%                                                                              
int main (void) {     
   extern FILE *yyin; 
   yyin = fopen("testfile_two.c", "r"); 
   yyparse ();{printf("Parsed Successfully\n");}
}
