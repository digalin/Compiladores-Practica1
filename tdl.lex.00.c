#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define AND 257
#define BREAK 258
#define CONST_INT 259
#define CONST_REAL 260
#define CONTINUE 261
#define ELSE 262
#define END 263
#define ENDIF 264
#define ENDWHILE 265
#define EQ 266
#define FALSE 267
#define GE 268
#define IDENTIFIER 269
#define IF 270
#define INT 271
#define LE 272
#define NE 273
#define NOT 274
#define OR 275
#define PROGRAM 276
#define READ 277
#define REAL 278
#define STOP 279
#define STRING 280
#define THEN 281
#define TRUE 282
#define WHILE 283
#define WRITE 284
#define WRITELN 285

#define ERROR_LEXICAL -1 /* Error léxico, no perteneciente a Σ */

FILE* yyin = NULL;
int yylineno = 1;
char yytext[ 255];

int get_symbol(char* in_text);
int yylex(void);
    
int yylex(void) {
    int in_char = 0;
    int state = 0;
    int i = 0;

    while (1) {
        switch (state) {
            case 0: /* Estado inicial */
                in_char = fgetc(yyin);
                i = 0;
                yytext[i++] = in_char;
                
                if (in_char == EOF) {
                    state = 40;
                    break;
                }
                
                if (in_char == ' ' || in_char == '\t') {
                    state = 1;
                } else if (in_char == '\n') {
                    state = 3;
                } else if (in_char == '#') {
                    state = 4;
                } else if (isalpha(in_char) || in_char == '_') {
                    state = 6;
                } else if (isdigit(in_char)) {
                    state = 8;
                } else if (in_char == '"') {
                    state = 17;
                } else if (in_char == '=') {
                    state = 20;
                } else if (in_char == '>') {
                    state = 23;
                } else if (in_char == '<') {
                    state = 26;
                } else if (in_char == '!') {
                    state = 29;
                } else if (in_char == '+') {
                    state = 32;
                } else if (in_char == '-') {
                    state = 33;
                } else if (in_char == '*') {
                    state = 34;
                } else if (in_char == '/') {
                    state = 35;
                } else if (in_char == ',') {
                    state = 36;
                } else if (in_char == ';') {
                    state = 37;
                } else if (in_char == '(') {
                    state = 38;
                } else if (in_char == ')') {
                    state = 39;
                } else {
                    state = 41; 
                }
                break;
                
            case 1: /* Espacios y tabuladores */
                in_char = fgetc(yyin);
                if (in_char == ' ' || in_char == '\t') {
                    state = 1;
                } else {
                    ungetc(in_char, yyin);
                    state = 2;
                }
                break;
                
            case 2: /* Aceptar espacios en blanco */
                state = 0;
                break;
                
            case 3: /* Salto de línea */
                yylineno++;
                state = 0;
                break;
                
            case 4: /* Comentario (después de #) */
                in_char = fgetc(yyin);
                if (in_char == '\n') {
                    state = 5;
                } else if (in_char == EOF) {
                    state = 39;
                } else {
                    state = 4;
                }
                break;
                
            case 5: /* Fin de comentario */
                yylineno++;
                state = 0;
                break;
                
            case 6: /* Identificadores */
                in_char = fgetc(yyin);
                if (isalnum(in_char) || in_char == '_') {
                    yytext[i++] = in_char;
                    state = 6;
                } else {
                    ungetc(in_char, yyin);
                    state = 7;
                }
                break;
                
            case 7: /* Aceptar identificador */
                yytext[i] = '\0';
                return get_symbol(yytext);
                
            case 8: /* Números enteros */
                in_char = fgetc(yyin);
                if (isdigit(in_char)) {
                    yytext[i++] = in_char;
                    state = 8;
                } else if (in_char == '.') {
                    yytext[i++] = in_char;
                    state = 9;
                } else {
                    ungetc(in_char, yyin);
                    state = 16;
                }
                break;
                
            case 9: /* Después del punto decimal */
                in_char = fgetc(yyin);
                if (isdigit(in_char)) {
                    yytext[i++] = in_char;
                    state = 10;
                } else {
                    ungetc(in_char, yyin);
                    state = 15; /* Error léxico, debe terminar con dígito(s) */
                }
                break;
                
            case 10: /* Parte fraccionaria */
                in_char = fgetc(yyin);
                if (isdigit(in_char)) {
                    yytext[i++] = in_char;
                    state = 10;
                } else if (in_char == 'e' || in_char == 'E') {
                    yytext[i++] = in_char;
                    state = 11;
                } else {
                    ungetc(in_char, yyin);
                    state = 14;
                }
                break;
                
            case 11: /* Exponente (e/E) */
                in_char = fgetc(yyin);
                if (in_char == '+' || in_char == '-') {
                    yytext[i++] = in_char;
                    state = 12;
                } else if (isdigit(in_char)) {
                    yytext[i++] = in_char;
                    state = 13;
                } else {
                    state = 15;
                }
                break;
                
            case 12: /* Signo del exponente */
                in_char = fgetc(yyin);
                if (isdigit(in_char)) {
                    yytext[i++] = in_char;
                    state = 13;
                } else {
                    state = 15; 
                }
                break;
                
            case 13: /* Dígitos del exponente */
                in_char = fgetc(yyin);
                if (isdigit(in_char)) {
                    yytext[i++] = in_char;
                    state = 13;
                } else {
                    ungetc(in_char, yyin);
                    state = 14;
                }
                break;
                
            case 14: /* Aceptar número real */
                yytext[i] = '\0';
                return CONST_REAL;

            case 15: /* Error léxico: número no válido */
                yytext[i] = '\0';
                return ERROR_LEXICAL; /* Debe terminar con dígito(s) */

            case 16: /* Aceptar número entero */
                yytext[i] = '\0';
                return CONST_INT;

            case 17: /* Cadena (después de ") */
                in_char = fgetc(yyin);
                if (in_char == '"') {
                    yytext[i++] = in_char;
                    state = 18;
                } else if (in_char == '\n') {
                    ungetc(in_char, yyin);
                    state = 19;
                } else {
                    yytext[i++] = in_char;
                    state = 17;
                }
                break;
                
            case 18: /* Retonar cadena */
                yytext[i] = '\0';
                return STRING;

            case 19: /* Cadena no aceptada */
                yytext[i] = '\0';
                return ERROR_LEXICAL; /* Debe cerrar con comillas (ej: "ejemplo válido") */

            case 20: /* = */
                in_char = fgetc(yyin);
                if (in_char == '=') {
                    yytext[i++] = in_char;
                    state = 21;
                } else {
                    ungetc(in_char, yyin);
                    state = 22;
                }
                break;
                
            case 21: /* == */
                yytext[i] = '\0'; 
                return EQ;
                
            case 22: /* = */
                yytext[i] = '\0'; 
                return '=';
                
            case 23: /* > */
                in_char = fgetc(yyin);
                if (in_char == '=') {
                    yytext[i++] = in_char;
                    state = 24;
                } else {
                    ungetc(in_char, yyin);
                    state = 25;
                }
                break;
                
            case 24: /* >= */
                yytext[i] = '\0'; 
                return GE;
                
            case 25: /* > */
                yytext[i] = '\0'; 
                return '>'; 
                
            case 26: /* < */
                in_char = fgetc(yyin);
                if (in_char == '=') {
                    yytext[i++] = in_char;
                    state = 27;
                } else {
                    ungetc(in_char, yyin);
                    state = 28;
                }
                break;
                
            case 27: /* <= */
                yytext[i] = '\0'; 
                return LE; 
                
            case 28: /* < */
                yytext[i] = '\0'; 
                return '<';

            case 29: /* ! */
                in_char = fgetc(yyin);
                if (in_char == '=') {
                    yytext[i++] = in_char;
                    state = 30;
                } else {
                    ungetc(in_char, yyin);
                    state = 31;
                }
                break;
                
            case 30: /* != */
                yytext[i] = '\0'; 
                return NE;

            case 31: /* ! solo */
                yytext[i] = '\0';
                return ERROR_LEXICAL;
                
            case 32: /* + */
                yytext[i] = '\0'; 
                return '+';
                
            case 33: /* - */
                yytext[i] = '\0'; 
                return '-'; 
                
            case 34: /* * */
                yytext[i] = '\0'; 
                return '*'; 
                
            case 35: /* / */
                yytext[i] = '\0'; 
                return '/'; 
                
            case 36: /* , */
                yytext[i] = '\0'; 
                return ','; 
                
            case 37: /* ; */
                yytext[i] = '\0';
                return ';';
                
            case 38: /* ( */
                yytext[i] = '\0'; 
                return '(';
                
            case 39: /* ) */
                yytext[i] = '\0';
                return ')';
                
            case 40: /* EOF */
                return 0;
                
            case 41: /* Otros caracteres */
                yytext[i] = '\0';
                return ERROR_LEXICAL;
        }
    }
}

int get_symbol(char* in_text) {
    if (strcmp(in_text, "and") == 0) return AND;
    else if (strcmp(in_text, "break") == 0) return BREAK;
    else if (strcmp(in_text, "continue") == 0) return CONTINUE;
    else if (strcmp(in_text, "else") == 0) return ELSE;
    else if (strcmp(in_text, "end") == 0) return END;
    else if (strcmp(in_text, "endif") == 0) return ENDIF;
    else if (strcmp(in_text, "endwhile") == 0) return ENDWHILE;
    else if (strcmp(in_text, "false") == 0) return FALSE;
    else if (strcmp(in_text, "if") == 0) return IF;
    else if (strcmp(in_text, "int") == 0) return INT;
    else if (strcmp(in_text, "not") == 0) return NOT;
    else if (strcmp(in_text, "or") == 0) return OR;
    else if (strcmp(in_text, "program") == 0) return PROGRAM;
    else if (strcmp(in_text, "read") == 0) return READ;
    else if (strcmp(in_text, "real") == 0) return REAL;
    else if (strcmp(in_text, "stop") == 0) return STOP;
    else if (strcmp(in_text, "then") == 0) return THEN;
    else if (strcmp(in_text, "true") == 0) return TRUE;
    else if (strcmp(in_text, "while") == 0) return WHILE;
    else if (strcmp(in_text, "write") == 0) return WRITE;
    else if (strcmp(in_text, "writeln") == 0) return WRITELN;
    else return IDENTIFIER;
}