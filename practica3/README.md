# Práctica 3 — Compilador TDL (Flex + Yacc/Bison)

Resumen
- Desarrollo de un compilador completo para el lenguaje TDL usando generadores automáticos: Flex (léxico) y Berkeley Yacc (sintáctico).
- Evolución de la Práctica 2: ahora se soporta el lenguaje completo (expresiones, condiciones, estructuras de control y recuperación de errores).

Gramática (BNF)
```
P  : PROGRAM LD LS END
LD : LD D | D
D  : INT LV ';' | REAL LV ';'
LV : LV ',' IDENTIFIER | IDENTIFIER
LS : LS S | S
S  : ';'
   | IDENTIFIER '=' E ';'
   | READ IDENTIFIER ';'
   | WRITE LP ';'
   | WRITELN ';'
   | IF C THEN LS ENDIF
   | IF C THEN LS ELSE LS ENDIF
   | WHILE C THEN LS ENDWHILE
   | STOP ';' | BREAK ';' | CONTINUE ';'
E  : E '+' E | E '-' E | E '*' E | E '/' E
   | '(' E ')' | '-' E
   | IDENTIFIER | CONST_INT | CONST_REAL
LP : LP ',' PAR | PAR
PAR: IDENTIFIER | CONST_INT | CONST_REAL | STRING
C  : C AND C | C OR C | '(' C ')' | NOT C
   | E '<' E | E '>' E | E '<=' E | E '>=' E | E '==' E | E '!=' E
   | TRUE | FALSE
```

Precedencia y asociatividad (resuelve ambigüedades)
```
%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS NOT
```

Estructura del directorio (tdl.02/)
- tdl.02.byacc — especificación de la gramática Berkeley Yacc
- tdl.02.flex — especificación del analizador léxico Flex
- main.02.c, yyerror.02.c — runtime (producción)
- Ejemplos de entrada: archivos *.tdl

Compilación
Desde el directorio que contiene las especificaciones ejecutar:
```sh
byacc -d tdl.02.byacc
flex tdl.02.flex
gcc -o tdl main.02.c yyerror.02.c y.tab.c lex.yy.c -lfl
```

o directamente
```sh
make
```

Genera:
- `tdl` — versión de producción

Ejecución
```sh
./tdl programa.tdl
```
- `tdl` no muestra salida si el programa es válido.

Manejo de errores
- El parser reporta tipo de error, línea y token problemático mediante las funciones en `yyerror.02.c`.
- La gramática incluye mecanismos de recuperación de errores para continuar el análisis cuando es posible.
