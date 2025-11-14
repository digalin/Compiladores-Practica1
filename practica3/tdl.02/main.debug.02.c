#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern FILE *yyin;
extern int yyparse();
extern int yyerrors;

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

    // Mostrar contenido del archivo línea por línea antes del análisis
    //  Esto con el fin de depurar errores de sintaxis asociados a líneas específicas.
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int line_num = 1;

        printf("===== ANÁLISIS PROFUNDO DE ARCHIVOS =====\n");
        while ((read = getline(&line, &len, yyin)) != -1)
        {
            printf("Linea %d: %s", line_num, line);
            line_num++;
        }
        printf("===== ANÁLISIS FINALIZADO (Lineas procesadas: %d) =====\n\n", line_num - 1);

        free(line);
        rewind(yyin); // Reiniciar el puntero del archivo para que el parser pueda leerlo desde el inicio.
    }

    int parse_result = yyparse();
    fclose(yyin);

    // Reportar resultado final del análisis sintáctico
    if (parse_result == 0 && yyerrors == 0)
    {
        printf("Compilación exitosa con %d errores.\n", yyerrors);
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Compilación fallida con %d errores detectados.\n", yyerrors);
        return EXIT_FAILURE;
    }
}