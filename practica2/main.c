#include <stdio.h>
#include <stdlib.h>
extern int P();
extern int check_last_token();
extern int yylineno;
extern FILE *yyin;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stdout, "Use: ./tdl <in_file_name: char*>.\n");
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
	P();
	if (check_last_token() != 0)
		fprintf(stderr, "tdl: syntax error at line %d.\n", yylineno);
  return EXIT_SUCCESS;
}
