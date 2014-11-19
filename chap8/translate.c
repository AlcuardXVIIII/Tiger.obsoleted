#include <stdio.h>
#include <assert.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "translate.h"

Tr_access Tr_Access(F_access access,Tr_level level){
  Tr_access tr_access = checked_malloc(sizeof(*tr_access));
  tr_access->access = access;
  tr_access->level = level;
  return tr_access;
}
Tr_accessList Tr_AccessList(Tr_access head,Tr_accessList tail){
  Tr_accessList tr_accessList = checked_malloc(sizeof(*tr_accessList));
  tr_accessList->head = head;
  tr_accessList->tail = tail;
  return tr_accessList;
}

static struct S_symbol_ outmark = {.name="<outermost>",.next=NULL};
static struct F_frame_ outframe = {.name=&outmark,.formals=NULL,.max_offset=0};
static struct Tr_level_ tr_outermost = {.parent=NULL,.name=&outmark,.frame=&outframe,.formals=NULL};

Tr_level Tr_outermost(){
  return &tr_outermost;
}
Tr_level Tr_newLevel(Tr_level parent,Temp_label name,U_boolList formals){
  Tr_level tr_level = checked_malloc(sizeof(*tr_level));

  tr_level->parent = parent;
  tr_level->name = name;
  tr_level->frame = F_newFrame(name,U_BoolList(TRUE,formals));
  F_accessList f_accessList = tr_level->frame->formals;
  Tr_accessList tr_accessList_h=NULL,tr_accessList_t=NULL;
  while(f_accessList!=NULL){
    Tr_accessList tr_accessList = Tr_AccessList(Tr_Access(f_accessList->head,tr_level),NULL);
    if(tr_accessList_t==NULL){
      tr_accessList_t = tr_accessList_h = tr_accessList;
    }else{
      tr_accessList_t->tail = tr_accessList;
      tr_accessList_t = tr_accessList_t->tail;
    }
    f_accessList = f_accessList->tail;
  }
  tr_level->formals = tr_accessList_h;
  return tr_level;
}
Tr_access Tr_allocLocal(Tr_level level,bool escape){
  F_frame frame = level->frame;
  F_access f_access = F_allocLocal(frame,escape);
  Tr_access tr_access = checked_malloc(sizeof(*tr_access));
  tr_access->access = f_access;
  tr_access->level = level;
  return tr_access;
}

struct Cx{patchList trues;patchList falses;T_stm stm;};
struct Tr_exp_{
  enum{Tr_ex,Tr_nx,Tr_cx}kind;
  union{T_exp ex;T_stm nx;struct Cx cx;}u;
};
static Tr_exp Tr_Ex(T_exp ex){
  Tr_exp tr_exp = checked_malloc(sizeof(*tr_exp));
  tr_exp->kind = Tr_ex;
  tr_exp->u.ex = ex;
  return tr_exp;
}
static Tr_exp Tr_Nx(T_stm stm){
  Tr_exp tr_exp = checked_malloc(sizeof(*tr_exp));
  tr_exp->kind = Tr_nx;
  tr_exp->u.nx = stm;
  return tr_exp;
}
static Tr_exp Tr_Cx(patchList trues,patchList falses,T_stm stm){
  Tr_exp tr_exp = checked_malloc(sizeof(*tr_exp));
  tr_exp->kind = Tr_cx;
  tr_exp->u.cx.trues = trues;
  tr_exp->u.cx.falses = falses;
  tr_exp->u.cx.stm = stm;
  return tr_exp;
}
static T_exp unEx(Tr_exp exp){
  if(exp==NULL){
    return unEx(Tr_nop());
  }
  switch(exp->kind){
  case Tr_ex:{
      return exp->u.ex;
    break;
    }
  case  Tr_nx:{
    return T_Eseq(exp->u.nx,T_Const(0));
    }
  case  Tr_cx:{
    Temp_temp r = Temp_newtemp();
    Temp_label t = Temp_newlabel(),f = Temp_newlabel();
    doPatch(exp->u.cx.trues,t);
    doPatch(exp->u.cx.falses,f);
    return T_Eseq(T_Move(T_Temp(r),T_Const(1)),
                  T_Eseq(exp->u.cx.stm,
                         T_Eseq(T_Label(f),
                                T_Eseq(T_Move(T_Temp(r),T_Const(0)),
                                       T_Eseq(T_Label(t),
                                              T_Temp(r))))));
    }
  }
  assert(0);
}
static T_stm unNx(Tr_exp exp){
  if(exp==NULL){
    return unNx(Tr_nop());
  }
  switch(exp->kind){
  case Tr_ex:
    return T_Exp(exp->u.ex);
  case Tr_nx:
    return exp->u.nx;
  case Tr_cx:{
    Temp_temp r = Temp_newtemp();
    Temp_label t = Temp_newlabel(),f = Temp_newlabel();
    doPatch(exp->u.cx.trues,t);
    doPatch(exp->u.cx.falses,f);
    return T_Exp(T_Eseq(T_Move(T_Temp(r),T_Const(1)),
                  T_Eseq(exp->u.cx.stm,
                         T_Eseq(T_Label(f),
                                T_Eseq(T_Move(T_Temp(r),T_Const(0)),
                                       T_Eseq(T_Label(t),
                                              T_Temp(r)))))));
  }
  }
  assert(0);
}
static struct Cx unCx(Tr_exp exp){
  struct Cx cx;
  switch(exp->kind){
  case Tr_ex:{
    struct Cx cx;
    cx.stm =T_Cjump(T_eq,exp->u.ex,T_Const(0),NULL,NULL);
    cx.trues = PatchList(&cx.stm->u.CJUMP.false,NULL);
    cx.falses = PatchList(&cx.stm->u.CJUMP.true,NULL);
    return cx;
  }
  case Tr_nx:
    assert(0);
    return cx;
  case Tr_cx:
    return exp->u.cx;
  }
  assert(0);
  return cx;
}
void doPatch(patchList ptList,Temp_label label){
  while(ptList!=NULL){
    *(ptList->head) = label;
    ptList = ptList->tail;
  }
}
patchList joinPatch(patchList first,patchList second){
  patchList patList_h = NULL,patList_t = NULL;;

  while(first!=NULL||second!=NULL){
    if(first!=NULL){
      patchList tmp = PatchList(first->head,NULL);
      if(patList_t==NULL){
        patList_h = patList_t = tmp;
      }else{
        patList_t->tail = tmp;
        patList_t = patList_t->tail;
      }
      first = first->tail;
    }
    else{
      patchList tmp = PatchList(second->head,NULL);
      if(patList_t==NULL){
        patList_h = patList_t = tmp;
      }else{
        patList_t->tail = tmp;
        patList_t = patList_t->tail;
      }
      second = second->tail;
    }
  }
  return patList_h;
  /*
  if(first==NULL)
    return second;
    while(first->tail!=NULL){
      first = first->tail;
    }
    first->tail = second;
    return first;*/
}
Tr_exp Tr_simpleVar(Tr_access tr_access,Tr_level curLevel){
  F_access f_access = tr_access->access;
  Tr_level tr_level = tr_access->level;
  T_exp t_exp = T_Temp(F_FP());
  while(tr_level!=curLevel){
    t_exp = F_Exp(curLevel->formals->head->access,t_exp);
    curLevel = curLevel->parent;
  }
  return Tr_Ex(F_Exp(f_access,t_exp));
}
T_exp staticLink(Tr_level curLevel,Tr_level desLevel){
  T_exp t_exp = T_Temp(F_FP());
  while(curLevel!=desLevel->parent){
    t_exp = F_Exp(curLevel->formals->head->access,t_exp);
    curLevel = curLevel->parent;
  }
  return t_exp;
}
Tr_exp Tr_fieldVar(Tr_exp var,int offset){
  return Tr_Ex(T_Mem(T_Binop(T_plus,unEx(var),T_Const(offset*F_wordSize))));
}
Tr_exp Tr_subscriptVar(Tr_exp var,Tr_exp index){
  return Tr_Ex(T_Mem(T_Binop(T_plus,unEx(var),T_Binop(T_mul,unEx(index),T_Const(F_wordSize)))));
}
Tr_exp Tr_opExp(A_oper oper,Tr_exp left,Tr_exp right){
  if(oper == A_plusOp){
    return Tr_Ex(T_Binop(T_plus,unEx(left),unEx(right)));
  }
  if(oper == A_minusOp){
    return Tr_Ex(T_Binop(T_minus,unEx(left),unEx(right)));
  }
  if(oper == A_timesOp){
    return Tr_Ex(T_Binop(T_mul,unEx(left),unEx(right)));
  }
  if(oper == A_divideOp){
    return Tr_Ex(T_Binop(T_div,unEx(left),unEx(right)));
  }
  assert(0);
}
Tr_exp Tr_relExp(A_oper oper,Tr_exp left,Tr_exp right){
  T_relOp t_relOp;
  switch(oper){
  case A_eqOp:
    t_relOp = T_eq;
    break;
  case A_neqOp:
    t_relOp = T_ne;
    break;
  case A_ltOp:
    t_relOp = T_lt;
    break;
  case A_leOp:
    t_relOp = T_le;
    break;
  case A_gtOp:
    t_relOp = T_gt;
    break;
  case A_geOp:
    t_relOp = T_ge;
    break;
  case A_andOp:{
    struct Cx cx_l = unCx(left);
    struct Cx cx_r = unCx(right);
    patchList patchTr = cx_r.trues;
    patchList patchFa = joinPatch(cx_l.falses,cx_r.falses);
    Temp_label temp_label = Temp_newlabel();
    doPatch(cx_l.trues,temp_label);
    T_stm t_stm = T_Seq(cx_l.stm,
                        T_Seq(T_Label(temp_label),
                              cx_r.stm));
    return Tr_Cx(patchTr,patchFa,t_stm);
  }
  case A_orOp:{
    struct Cx cx_l = unCx(left);
    struct Cx cx_r = unCx(right);
    patchList patchTr = joinPatch(cx_l.trues,cx_r.trues);
    patchList patchFa = cx_r.falses;
    Temp_label temp_label = Temp_newlabel();
    doPatch(cx_l.falses,temp_label);
    T_stm t_stm = T_Seq(cx_l.stm,
                        T_Seq(T_Label(temp_label),
                              cx_r.stm));
    return Tr_Cx(patchTr,patchFa,t_stm);
  }
  default:
    assert(0);
  }
  T_stm t_stm = T_Cjump(t_relOp,unEx(left),unEx(right),NULL,NULL);
  patchList patTr = PatchList(&t_stm->u.CJUMP.true,NULL);
  patchList patFa = PatchList(&t_stm->u.CJUMP.false,NULL);
  return Tr_Cx(patTr,patFa,t_stm);
}
Tr_exp Tr_ifExp(Tr_exp test,Tr_exp thenn,Tr_exp elsee){

  if(test==NULL||thenn==NULL)
    return NULL;
  Temp_label t_label = Temp_newlabel();
  Temp_label f_label = Temp_newlabel();
  struct Cx cx = unCx(test);
  doPatch(cx.trues,t_label);
  doPatch(cx.falses,f_label);
  if(elsee==NULL){
    return Tr_Nx(T_Seq(cx.stm,
                       T_Seq(T_Label(t_label),
                              T_Seq(unNx(thenn),
                                    T_Label(f_label)))));

  }else{
    Temp_label r_label = Temp_newlabel();
    Temp_temp temp_temp = Temp_newtemp();
    T_stm jump_stm = T_Jump(T_Name(r_label),Temp_LabelList(r_label,NULL));
    switch(thenn->kind){
    case Tr_nx:
      return Tr_Nx(T_Seq(cx.stm,
                         T_Seq(T_Label(t_label),
                               T_Seq(unNx(thenn),
                                     T_Seq(jump_stm,
                                           T_Seq(T_Label(f_label),
                                                 T_Seq(unNx(elsee),
                                                       T_Label(r_label))))))));
      break;
    case Tr_ex:
    case Tr_cx:
      return Tr_Ex(T_Eseq(cx.stm,
                          T_Eseq(T_Label(t_label),
                                 T_Eseq(T_Move(T_Temp(temp_temp),unEx(thenn)),
                                        T_Eseq(jump_stm,
                                               T_Eseq(T_Label(f_label),
                                                      T_Eseq(T_Move(T_Temp(temp_temp),unEx(elsee)),
                                                             T_Eseq(T_Label(r_label),T_Temp(temp_temp)))))))));
      break;
    }
  }
  assert(0);
}
Tr_exp Tr_forExp(Tr_exp simpVar,Tr_exp lo,Tr_exp hi,Tr_exp body,patchList patList){
  Temp_label test_label = Temp_newlabel();
  Temp_label ok_label = Temp_newlabel();
  Temp_label done_label = Temp_newlabel();
  doPatch(patList,done_label);
  Temp_temp lo_temp = Temp_newtemp();
  Temp_temp hi_temp = Temp_newtemp();

  T_stm cjump = T_Cjump(T_gt,unEx(simpVar),T_Temp(hi_temp),NULL,NULL);
  patchList patList_t = PatchList(&(cjump->u.CJUMP.true),NULL);
  patchList patList_f = PatchList(&(cjump->u.CJUMP.false),NULL);
  doPatch(patList_t,done_label);
  doPatch(patList_f,ok_label);

  T_stm jump = T_Jump(T_Name(test_label),Temp_LabelList(test_label,NULL));

  Temp_temp temp = Temp_newtemp();
  T_stm plus = T_Seq(T_Move(T_Temp(temp),T_Mem(unEx(simpVar))),
                     T_Seq(T_Exp(T_Binop(T_plus,T_Temp(temp),T_Const(1))),
                           T_Move(T_Mem(unEx(simpVar)),T_Temp(temp))));
  T_stm t_stm = T_Seq(T_Move(T_Temp(lo_temp),unEx(lo)),
                      T_Seq(T_Move(T_Temp(hi_temp),unEx(hi)),
                            T_Seq(T_Move(unEx(simpVar),T_Temp(lo_temp)),
                                  T_Seq(T_Label(test_label),
                                        T_Seq(cjump,
                                              T_Seq(T_Label(ok_label),
                                                    T_Seq(unNx(body),
                                                          T_Seq(plus,
                                                                T_Seq(jump,
                                                                      T_Label(done_label))))))))));
  return Tr_Nx(t_stm);
}

Tr_exp Tr_whileExp(Tr_exp test,Tr_exp body,patchList patList){
  Temp_label test_label = Temp_newlabel();
  Temp_label ok_label = Temp_newlabel();
  Temp_label done_label = Temp_newlabel();
  doPatch(patList,done_label);
  struct Cx cx = unCx(test);
  doPatch(cx.trues,done_label);
  doPatch(cx.falses,ok_label);

  T_stm t_stm = T_Seq(T_Label(test_label),
                      T_Seq(cx.stm,
                            T_Seq(T_Jump(T_Name(done_label),Temp_LabelList(done_label,NULL)),
                                   T_Seq(T_Label(ok_label),
                                        T_Seq(unNx(body),
                                              T_Seq(T_Jump(T_Name(test_label),Temp_LabelList(test_label,NULL)),
                                                    T_Label(done_label)))))));

  return Tr_Nx(t_stm);
}
Tr_exp Tr_breakExp(patchList* patList){
      T_exp t_label = T_Name(NULL);
      (*patList) = PatchList(&(t_label->u.NAME),*patList);
      T_stm stm = T_Jump(t_label,Temp_LabelList(t_label->u.NAME,NULL));
      return Tr_Nx(stm);
}

Tr_exp Tr_callExp(Temp_label label,T_exp  staticLink,T_expList t_expList){
  return Tr_Ex(T_Call(T_Name(label),T_ExpList(staticLink,t_expList)));
}

Tr_exp Tr_nop(){
  return Tr_Ex(T_Const(0));
}
Tr_exp Tr_letExp(T_expList t_expList){
  T_exp t_exp = t_expList->head;
  for(t_expList = t_expList->tail;t_expList;t_expList=t_expList->tail){
    t_exp = T_Eseq(T_Exp(t_expList->head),t_exp);
  }
  return Tr_Ex(t_exp);

}
Tr_exp Tr_recordExp(int fieldNum,T_expList t_expList){
  Temp_temp r = Temp_newtemp();
  T_stm alloc = T_Move(T_Temp(r),
                       F_externalCall(String("initRecord"),T_ExpList(T_Const(fieldNum*F_wordSize),NULL)));
  T_exp t_exp = t_expList->head;
  t_expList = t_expList->tail;
  T_stm t_stm = T_Move(T_Mem(T_Binop(T_plus,T_Temp(r),T_Const(--fieldNum*F_wordSize))),t_exp);
  while(t_expList!=NULL){
    t_stm = T_Seq(T_Move(T_Mem(T_Binop(T_plus,T_Temp(r),T_Const(--fieldNum*F_wordSize))),t_expList->head),t_stm);
    t_expList = t_expList->tail;
  }
  return Tr_Ex(T_Eseq(T_Seq(alloc,t_stm),T_Temp(r)));
}
Tr_exp Tr_arrayExp(Tr_exp size,Tr_exp init){
  return Tr_Ex(F_externalCall(String("initArray"),
                              T_ExpList(unEx(size),T_ExpList(unEx(init),NULL))));
}
Tr_exp Tr_intExp(int n){
  return Tr_Ex(T_Const(n));
}
static F_fragList stringList = NULL;
static F_fragList procList = NULL;
Tr_exp Tr_stringExp(string str){
  Temp_label temp_label = Temp_newlabel();
  F_frag f_frag = F_StringFrag(temp_label,str);
  stringList = F_FragList(f_frag,stringList);
  return Tr_Ex(T_Name(temp_label));
}
Tr_exp Tr_nilExp(){
  static Temp_temp nil_temp = NULL;
  if(nil_temp!=NULL){
    return Tr_Ex(T_Temp(nil_temp));
  }
  else{
    nil_temp = Temp_newtemp();
    T_stm alloc = T_Move(T_Temp(nil_temp),
                       F_externalCall(String("initRecord"),T_ExpList(T_Const(0*F_wordSize),NULL)));
    return Tr_Ex(T_Eseq(alloc,T_Temp(nil_temp)));
  }
}

Tr_exp Tr_assignExp(Tr_exp var,Tr_exp exp){
  return Tr_Nx(T_Move(unEx(var),unEx(exp)));
}

Tr_exp Tr_seqExp(T_expList t_expList){
  if(t_expList==NULL){
    return Tr_nop();
  }

  T_exp t_exp = t_expList->head;
  t_expList = t_expList->tail;
  while(t_expList){
    t_exp = T_Eseq(T_Exp(t_expList->head),t_exp);
    t_expList = t_expList->tail;
  }
  return Tr_Ex(t_exp);
}
Tr_exp Tr_eqIntExp(A_oper oper,Tr_exp left,Tr_exp right){
  T_relOp t_relOp = T_eq;
  if (oper != A_eqOp) t_relOp = T_ne;
  T_stm t_stm = T_Cjump(t_relOp, unEx(left), unEx(right), NULL, NULL);
  patchList trues = PatchList(&t_stm->u.CJUMP.true, NULL);
  patchList falses = PatchList(&t_stm->u.CJUMP.false, NULL);
  return Tr_Cx(trues, falses, t_stm);
}
Tr_exp Tr_eqStringExp(A_oper oper,Tr_exp left,Tr_exp right){
  T_exp result = F_externalCall(String("stringEqual"),
                                T_ExpList(unEx(left), T_ExpList(unEx(right), NULL)));
  if(result->kind == T_CONST){
    if(result->u.CONST==0){
      if(oper == A_eqOp){
        return Tr_Ex(T_Const(0));
      }
      else{
        return  Tr_Ex(T_Const(1));
      }
    }else if(result->u.CONST==1){
      if(oper == A_eqOp){
        return Tr_Ex(T_Const(1));
      }
      else{
        return  Tr_Ex(T_Const(0));
      }
    }
  }
  assert(0);
}
Tr_exp Tr_eqRefExp(A_oper oper,Tr_exp left,Tr_exp right){
  T_relOp t_relOp = T_eq;
  if (oper != A_eqOp) t_relOp = T_ne;
  T_stm t_stm = T_Cjump(t_relOp, unEx(left), unEx(right), NULL, NULL);
  patchList trues = PatchList(&t_stm->u.CJUMP.true, NULL);
  patchList falses = PatchList(&t_stm->u.CJUMP.false, NULL);
  return Tr_Cx(trues, falses, t_stm);
}

void Tr_procEntryExit(Tr_level level,Tr_exp body){
  T_stm t_stm = T_Move(T_Temp(F_RV()),unEx(body));
  F_frag f_frag = F_ProcFrag(t_stm,level->frame);
  procList = F_FragList(f_frag,procList);
}
F_fragList Tr_getResult(){
  F_fragList f_fragList=stringList,p=NULL;
  while(f_fragList!=NULL){
    p = f_fragList;
    f_fragList = f_fragList->tail;
  }
  if(p!=NULL){
    p->tail = procList;
  }
  return stringList ? stringList : procList;
}

patchList PatchList(Temp_label* label,patchList tail){
  patchList patList = checked_malloc(sizeof(*patList));
  patList->head = label;
  patList->tail = tail;
  return patList;
}
T_expList Tr_ExpList(Tr_exp exp,T_expList tail){
  return T_ExpList(unEx(exp),tail);
}
