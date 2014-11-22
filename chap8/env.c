#include <stdio.h>
#include <assert.h>
#include "util.h"
#include "table.h"
#include "symbol.h"
#include "absyn.h"
#include "types.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "translate.h"
#include "env.h"

E_enventry E_VarEntry(Tr_access access,Ty_ty ty){
  E_enventry e = checked_malloc(sizeof(*e));
  e->kind = E_varEntry;
  e->u.var.access = access;
  e->u.var.ty = ty;
  return e;
}
E_enventry E_FunEntry(Tr_level level,Temp_label label,Ty_tyList formals,Ty_ty result){
  E_enventry e = checked_malloc(sizeof(*e));
  e->kind = E_funEntry;
  e->u.fun.level = level;
  e->u.fun.label = label;
  e->u.fun.formals = formals;
  e->u.fun.result = result;
  return e;
}
S_table E_base_tenv(void){
  S_table s_table = TAB_empty();
  S_enter(s_table,S_Symbol("int"),Ty_Int());
  S_enter(s_table,S_Symbol("string"),Ty_String());
  S_enter(s_table,S_Symbol("nil"),Ty_Nil());
  S_enter(s_table,S_Symbol("void"),Ty_Void());
  return s_table;
}
S_table E_base_venv(void){
  return TAB_empty();
}
void E_push(E_stack* stack,void *object){
  E_stack node = checked_malloc(sizeof(*node));
  node->object = object;
  node->next = *stack;
  *stack = node;
}
void E_pop(E_stack* stack){
  if(stack==NULL){
    fprintf(stdout,"stack already empty\n");
    assert(0);
  }
  if(*stack!=NULL){
    *stack =(*stack)->next;
  }
}
void* E_top(E_stack stack){
  if(stack==NULL){
    fprintf(stdout,"stack already empty\n");
    assert(0);
  }
  return stack->object;
}
E_stack E_newStack(){
  return NULL;
}
