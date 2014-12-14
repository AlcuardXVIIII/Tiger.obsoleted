#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "errormsg.h"
#include "table.h"
#include "symbol.h"
#include "absyn.h"
#include "prabsyn.h"
#include "types.h"
#include "temp.h"
#include "tree.h"
#include "escape.h"
#include "assem.h"
#include "frame.h"
#include "translate.h"
#include "printtree.h"
#include "env.h"
#include "bst.h"
#include "semant.h"
#include "canon.h"
#include "codegen.h"
#include "graph.h"
#include "flowgraph.h"
#include "liveness.h"
#include "color.h"
#include "regalloc.h"

extern int yyparse(void);
extern A_exp absyn_root;

A_exp parse(string fname){
  EM_reset(fname);
  if (yyparse() == 0){ /* parsing worked */
   fprintf(stderr,"Parsing successful!\n");
   return absyn_root;
  }
  fprintf(stderr,"Parsing failed\n");
  return NULL;
}

static E_stack stack;
void SEM_transProg(A_exp exp){
  S_table venv = E_base_venv();
  S_table tenv = E_base_tenv();
  stack = E_newStack();
  transExp(Tr_outermost(),venv,tenv,exp);
  F_fragList f_fragList = Tr_getResult();
  while(f_fragList!=NULL){
    F_frag f_frag = f_fragList->head;
    if(f_frag->kind==F_procFrag){
      T_stmList t_stmList = C_linearize(f_frag->u.proc.body);
      struct C_block block = C_basicBlocks(t_stmList);
      t_stmList = C_traceSchedule(block);
      //printStmList(stdout,t_stmList);
      F_frame f = f_frag->u.proc.frame;
      AS_instrList as_instrList = F_codegen(f,t_stmList);
      //AS_printInstrList(stdout,as_instrList,F_temp2Name());
      RA_result ra_result = RA_regAlloc(f,as_instrList);
      as_instrList =  prologue(f,ra_result->il);
      AS_printInstrList(stdout,as_instrList,ra_result->coloring);
    }
    else{
      fprintf(stdout,"%s:\n    .string %s\n",Temp_labelstring(f_frag->u.stringg.label),f_frag->u.stringg.str);
    }
    f_fragList = f_fragList->tail;
  }
}
int main(int argc, char **argv) {
 if (argc!=2) {
   fprintf(stderr,"usage: a.out filename\n"); exit(1);
 }
 A_exp exp = parse(argv[1]);
 if(exp==NULL){
   return 0;
 }
 Esc_findEscape(exp);
 //pr_exp(stdout,exp,4);
 // fprintf(stdout,"\n");
   SEM_transProg(exp);
   return 0;
}
