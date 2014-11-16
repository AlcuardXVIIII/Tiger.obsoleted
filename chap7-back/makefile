a.out: parsetest.o y.tab.o lex.yy.o errormsg.o util.o table.o symbol.o absyn.o prabsyn.o semant.o types.o env.o bst.o translate.o frame.o temp.o escape.o tree.o
	cc -g parsetest.o y.tab.o lex.yy.o errormsg.o util.o table.o symbol.o absyn.o prabsyn.o semant.o types.o env.o bst.o translate.o frame.o temp.o escape.o tree.o
tree.o: tree.c tree.h
	cc -g -c tree.c
frame.o: frame.c frame.h
	cc -g -c frame.c
escape.o: escape.c escape.h
	cc -g -c escape.c
parsetest.o: parsetest.c errormsg.h util.h
	cc -g -c parsetest.c
semant.o: semant.h semant.c
	cc -g -c semant.c
types.o: types.h types.c
	cc -g -c types.c
translate.o: translate.h translate.c
	cc -g -c translate.c
env.o: env.c env.h
	cc -g -c env.c
bst.o: bst.h bst.h
	cc -g -c bst.c
y.tab.o: y.tab.c absyn.h util.h table.h symbol.h 
	cc -g -c y.tab.c
y.tab.c: tiger.grm
	bison --yacc --report=lookahead -vd tiger.grm

y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

errormsg.o: errormsg.c errormsg.h util.h
	cc -g -c errormsg.c

lex.yy.o: lex.yy.c y.tab.h errormsg.h util.h absyn.h symbol.h table.h
	cc -g -c lex.yy.c
prabsyn: prabsyn.h prabsyn.c
	cc -g -c prabsyn.c
absyn.o: util.h symbol.h table.h
	cc -g -c absyn.c
symbol.o: util.h table.h
	cc -g -c symbol.c
table.o: util.h
	cc -g -c table.c
lex.yy.c: tiger.lex
	lex tiger.lex

util.o: util.c util.h
	cc -g -c util.c

clean: 
	rm -f a.out util.o parsetest.o lex.yy.o errormsg.o y.tab.c y.tab.h y.tab.o lex.yy.c y.output table.o absyn.o symbol.o errormsg.o  prabsyn.o env.o types.o semant.o frame.o bst.o translate.o temp.o escape.o tree.o
