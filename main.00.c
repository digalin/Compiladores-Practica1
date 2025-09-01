#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylineno;
extern FILE* yyin;
extern int yylex();
extern char yytext[255];

const char* get_token_name(int token) {
    switch(token) {
        case 257: return "AND";
        case 258: return "BREAK";
        case 259: return "CONST_INT";
        case 260: return "CONST_REAL";
        case 261: return "CONTINUE";
        case 262: return "ELSE";
        case 263: return "END";
        case 264: return "ENDIF";
        case 265: return "ENDWHILE";
        case 266: return "EQ";
        case 267: return "FALSE";
        case 268: return "GE";
        case 269: return "IDENTIFIER";
        case 270: return "IF";
        case 271: return "INT";
        case 272: return "LE";
        case 273: return "NE";
        case 274: return "NOT";
        case 275: return "OR";
        case 276: return "PROGRAM";
        case 277: return "READ";
        case 278: return "REAL";
        case 279: return "STOP";
        case 280: return "STRING";
        case 281: return "THEN";
        case 282: return "TRUE";
        case 283: return "WHILE";
        case 284: return "WRITE";
        case 285: return "WRITELN";
        default:
            static char buf[5];
            snprintf(buf, sizeof(buf), "'%c'", token);
            return buf;
    }
}

int main(int argc, char** argv) {
    int token = 0;
    int line_num = 1;
    
    if (argc != 2) {
        fprintf(stdout, "Use: lexer <in_file_name: char*>.\n");
        return EXIT_FAILURE;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stdout, "File \"%s\" could not be opened.\n", argv[1]);
        fprintf(stdout, "Check if the name is correct ");
        fprintf(stdout, "or if the file is damaged.\n");
        return EXIT_FAILURE;
    }

    
    fprintf(stdout, "LINE\tTOKEN ID\tTOKEN\t\tLEXEME\n");
    fprintf(stdout, "----------------------------------------------------------------\n");
    
    while ((token = yylex()) != 0) {
        // Almacenar el número de línea actual antes de leer el token en sí
        line_num = yylineno;
        
        const char* token_name = get_token_name(token);
        
        char display_text[256];
        strncpy(display_text, yytext, sizeof(display_text)-1);
        display_text[sizeof(display_text)-1] = '\0';
        
        // Salida de los datos de la tabla en columnas con: número de línea, ID del token, token y lexema
        fprintf(stdout, "%-8d\t%-12d\t%-20s\t%s\n", 
                line_num, token, token_name, display_text);
    }
    
    // Resumen con archivo leído y total de líneas analizadas
    fprintf(stdout, "\nlexer: file %s, %d lines scanned.\n", argv[1], yylineno);
    fclose(yyin);
    return EXIT_SUCCESS;
}
