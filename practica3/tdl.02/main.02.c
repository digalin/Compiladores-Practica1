#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
extern int yyparse();
int main(
    int argc,
    char **argv)
{
#ifdef YYDEBUG
   extern int yydebug;
   yydebug = 1;
#endif
   if (argc != 2)
   {
      fprintf(stdout, "Use: tdl <in_file_name: char*>.\n");
      return EXIT_FAILURE;
   }
   yyin = fopen(argv[1], "r");
   if (yyin == NULL)
   {
      fprintf(stdout, "File \"%s\" could not be opened.\n", argv[1]);
      fprintf(stdout, "Check if the name is correct ");
      fprintf(stdout, "or if the file is damaged.\n");
      exit(EXIT_FAILURE);
   }
   yyparse();
   fclose(yyin);

   return EXIT_SUCCESS;
}
