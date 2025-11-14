#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern char* yytext;
int yyerror
(
   char* s
)
{
   fprintf( stderr, "tdl, line %d: ", yylineno);
   fputs( s, stderr);
   fprintf( stderr, ", near of \'%s\'.\n", yytext);

   return EXIT_SUCCESS;
}
