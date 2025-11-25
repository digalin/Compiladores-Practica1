#
#   tdl Makefile
#
CC = gcc

tdl: y.tab.c lex.yy.c main.02.c yyerror.02.c
	${CC} -o tdl y.tab.c lex.yy.c main.02.c yyerror.02.c -lfl -w #-DYYDEBUG

y.tab.c: tdl.02.byacc 
	byacc -d tdl.02.byacc

lex.yy.c: tdl.02.flex
	flex tdl.02.flex

clean:
	(rm -f core) 
	(rm -f *.o)
	(rm -f *~)
	(rm -f tdl y.tab.c y.tab.h lex.yy.c)
