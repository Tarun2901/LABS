%x IN_COMMENT 

%{
    #include "y.tab.h"
    extern int line_number;

    void yyerror(char const *s) {
      fprintf(stderr, "line %d: Parsing error\n", line_number); 
      exit(0);
    }
 
    extern char* yytext;
%}
%option noyywrap    

%%

<INITIAL>"/*"         {BEGIN(IN_COMMENT);}
<IN_COMMENT>"*/"      {BEGIN(INITIAL);}
<IN_COMMENT>[^*\n]+   ;
<IN_COMMENT>"*"       ;
<IN_COMMENT>\n        {line_number++;}
<IN_COMMENT><<EOF>>   {
                        printf("UNTERMINATED COMMENT AT line %d!", line_number);
                        yyterminate();
                      }

"#include<"[a-zA-Z_]*".h>"|"#define"[a-zA-Z_ =+-;*&!%][ a-zA-Z0-9_ =+-;*&!%]* return HEADER;
"int"                       return INT;
"void"                      return VOID;
"+"                         return PLUS;
"="                         return ASSIGNMENT;
";"                         return EOL;
","                         return COMMA;
"{"                         return LEFT_PARANTHESIS;
"}"                         return RIGHT_PARANTHESIS;
"("                         return LEFT_BRACKET;
")"                         return RIGHT_BRACKET;
[a-zA-Z][a-zA-Z]*           return ID;
[0-9][0-9]*                 return NUM;
[ \t\r]+                    ;
[\n]                        {line_number++;}
[a-zA-Z0-9]+                yyerror("Identifier must consist only alphabetical characters!");
[*][/]                      yyerror("not initialized comment!");
.                           yyerror("Error in Syntax!");


