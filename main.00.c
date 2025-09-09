#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern FILE* yyin;
extern int yylex();

int main(int argc, char** argv) {
    int token = 0;
    if (argc != 2) {
        fprintf(stdout, "Uso: lexer <nombre_de_archivo: char*>.\n");
        return EXIT_FAILURE;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stdout, "Archivo \"%s\" no se pudo abrir.\n", argv[1]);
        fprintf(stdout, "Verifique si el nombre es correcto, válido ");
        fprintf(stdout, "o si el archivo está dañado.\n");
        return EXIT_FAILURE;
    }

    while ((token = yylex()) != 0) {
        fprintf(stdout, "%d ", token);
    }
    fprintf(stdout, "\nlexer: archivo %s, %d líneas analizadas.\n", argv[1], yylineno);
    fclose(yyin);
    return EXIT_SUCCESS;
}
