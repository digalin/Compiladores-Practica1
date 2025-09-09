#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern FILE* yyin; // Archivo de entrada para el lexer
extern int yylex(); // Función principal del analizador léxico

int main(int argc, char** argv) {
    int token = 0;
    int prev_line = 0; // Guarda el número de la línea anterior

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

    // Procesa los tokens generados por el lexer
    while ((token = yylex()) != 0) {
        // Si cambia la línea, imprime el número de línea y un salto de línea si no es la primera vez
        if (yylineno != prev_line) {
            if (prev_line != 0) fprintf(stdout, "\n");
            fprintf(stdout, "%3d: ", yylineno);
            prev_line = yylineno;
        }
        // Imprime el valor del token reconocido
        fprintf(stdout, "%d ", token);
    }
     
    // Imprime un resumen de las líneas analizadas
    fprintf(stdout, "\nlexer: archivo %s, %d líneas analizadas.\n", argv[1], yylineno);
    fclose(yyin);
    return EXIT_SUCCESS;
}
