%{
#include "y.tab.h"
%}
letter   [A-Za-z]
digit    [0-9]
digits   {digit}+
fraction ("."{digits})
exponent (E[+-]?{digits})
%%
[ \t]+   ;
\n       yylineno++;
and      return AND;
break    return BREAK;
continue return CONTINUE;
else     return ELSE;
end      return END;
endif    return ENDIF;
endwhile return ENDWHILE;
false    return FALSE;
if       return IF;
int      return INT;
not      return NOT;
or       return OR;
program  return PROGRAM;
read     return READ;
real     return REAL;
stop     return STOP;
then     return THEN;
true     return TRUE;
while    return WHILE;
write    return WRITE;
writeln  return WRITELN;
{digits} return CONST_INT;
({letter}|_)({letter}|{digit}|_)*  return IDENTIFIER;
{digits}{fraction}{exponent}?      return CONST_REAL;
\"[^\"\n]*\"                       return STRING;
"=="     return EQ;
">="     return GE;
"<="     return LE;
"!="     return NE;
.        return yytext[0];
%%
