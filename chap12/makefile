a.out: parsetest.o y.tab.o lex.yy.o errormsg.o util.o table.o symbol.o absyn.o prabsyn.o semant.o types.o env.o bst.o translate.o frame.o temp.o escape.o tree.o canon.o printtree.o assem.o codegen.o graph.o flowgraph.o liveness.o regalloc.o color.o
	cc -g parsetest.o y.tab.o lex.yy.o errormsg.o util.o table.o symbol.o absyn.o prabsyn.o semant.o types.o env.o bst.o translate.o frame.o temp.o escape.o tree.o canon.o printtree.o assem.o codegen.o graph.o flowgraph.o liveness.o regalloc.o color.o
regalloc.o:regalloc.c regalloc.h
	cc -g -c regalloc.c
color.o:color.c color.h
	cc -g -c color.c
liveness.o:liveness.c liveness.h
	cc -g -c liveness.c
flowgraph.o:flowgraph.c flowgraph.h
	cc -g -c flowgraph.c
graph.o: graph.h graph.c
	cc -g -c graph.c
codegen.o:codegen.c codegen.h
	cc -g -c codegen.c
assem.o: assem.h assem.c
	cc -g -c assem.c
printtree: printtree.h printtree.c
	cc -g -c printtree.c
canon.o: canon.c canon.h
	cc -g -c canon.c
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
	rm -f a.out util.o parsetest.o lex.yy.o errormsg.o y.tab.c y.tab.h y.tab.o lex.yy.c y.output table.o absyn.o symbol.o errormsg.o  prabsyn.o env.o types.o semant.o frame.o bst.o translate.o temp.o escape.o tree.o canon.o printtree.o codegen.o assem.o graph.o flowgraph.o liveness.o regalloc.o color.o
