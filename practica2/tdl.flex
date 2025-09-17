%{
#include "define.h"
%}

letter [A-Za-z]
digit [0-9]
digits {digit}+
fraction ("."{digits})
exponent ([eE][+-]?{digits})
string \"[^"\n]*\"
%%

[ \t]+ ;
\n yylineno++;

end                                 return END;
int                                 return INT;
program                             return PROGRAM;
read                                return READ;
real                                return REAL;
write                               return WRITE;
writeln                             return WRITELN;

{digits}                            return CONST_INT;
{digits}{fraction}{exponent}?       return CONST_REAL;
{string}                            return STRING;
({letter}|_)({letter}|{digit}|_)*   return IDENTIFIER;

","                                 return ',';
";"                                 return ';';

.                                   return ERROR_LEXICAL;
%%