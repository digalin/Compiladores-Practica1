#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern char *yytext;
int yyerrors = 0;
int yyerror(
    char *s)
{
    fprintf(stderr, "tdl, line %d: ", yylineno);
    fputs(s, stderr);
    fprintf(stderr, ", near of \'%s\'.\n", yytext);
    yyerrors++;
    return EXIT_SUCCESS;
}
