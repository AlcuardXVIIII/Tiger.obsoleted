#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "errormsg.h"
#include "table.h"
#include "symbol.h"
#include "absyn.h"
#include "types.h"
#include "temp.h"
#include "frame.h"
#include "translate.h"
#include "env.h"
#include "tree.h"
#include "semant.h"

void SEM_transProg(A_exp exp){
  S_table venv = E_base_venv();
  S_table tenv = E_base_tenv();
  transExp(Tr_outermost(),venv,tenv,exp);
}
bool assertSameType(Ty_ty ty1,Ty_ty ty2){
  if(ty1==NULL||ty2==NULL)
    return 0;
  if(ty1->kind==Ty_nil&&ty2->kind==Ty_record)
    return 1;
  if(ty2->kind==Ty_nil&&ty1->kind==Ty_record)
    return 1;
  return(ty1==ty2);
}
Ty_ty actualTy(Ty_ty ty){

  Ty_ty t = ty;
  while(t!=NULL&&t->kind==Ty_name){
    t = t->u.name.ty;
  }
  return t;
}

Tr_expty transVar(Tr_level level,S_table venv,S_table tenv,A_var v){
  switch(v->kind){
  case A_simpleVar:{
    E_enventry e_enventry = S_look(venv,v->u.simple);
    if(!e_enventry || e_enventry->kind != E_varEntry){
      EM_error(v->pos,"no exist variable");
      return Expty(NULL,NULL);
    }else{
      return Expty(NULL,actualTy(e_enventry->u.var.ty));
    }
  }
  case A_fieldVar:{
    Tr_expty upLevel = transVar(level,venv,tenv,v->u.field.var);
    if(upLevel->ty==NULL){
      return Expty(NULL,NULL);
    }else{
      if(upLevel->ty->kind!=Ty_record){
        EM_error(v->pos,"no record type");
      }
      Ty_fieldList ty_fieldList = upLevel->ty->u.record;
      Ty_field ty_field = NULL;
      while(ty_fieldList!=NULL){
        if(ty_fieldList->head->name == v->u.field.sym){
          ty_field = ty_fieldList->head;
          break;
        }
        ty_fieldList= ty_fieldList->tail;
      }
      if(ty_field == NULL){
        EM_error(v->pos,"No exist field");
        return Expty(NULL,NULL);
      }else {
        return Expty(NULL,actualTy(ty_field->ty));
      }
    }

  }
  case A_subscriptVar:{
    Tr_expty var_expty = transVar(level,venv,tenv,v->u.subscript.var);
    Tr_expty exp_expty = transExp(level,venv,tenv,v->u.subscript.exp);
    if(exp_expty->ty->kind!=Ty_int){
      EM_error(v->pos,"index must be int type");
    }
    if(var_expty->ty->kind!=Ty_array){
      EM_error(v->pos,"the type of var must be an array");
    }
    return Expty(NULL,actualTy(var_expty->ty->u.array));
  }
  }
  return Expty(NULL,NULL);
}
Tr_expty transExp(Tr_level level,S_table venv,S_table tenv,A_exp a){
  switch(a->kind){
  case A_opExp:{
    A_oper oper = a->u.op.oper;

    Tr_expty left = transExp(level,venv,tenv,a->u.op.left);

    Tr_expty right = transExp(level,venv,tenv,a->u.op.right);
    if(left->ty==NULL || right->ty==NULL){
      return Expty(NULL,NULL);
    }
    if(oper == A_plusOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_minusOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_timesOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_divideOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_eqOp){
      if(!assertSameType(left->ty,right->ty)){
        EM_error(a->pos,"need same type");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_neqOp){
      if(!assertSameType(left->ty,right->ty)){
        EM_error(a->pos,"need same type");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_ltOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_leOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_gtOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    if(oper == A_geOp){
      if(left->ty->kind!=Ty_int){
        EM_error(a->u.op.left->pos,"integer required");
      }
      if(right->ty->kind!=Ty_int){
        EM_error(a->u.op.right->pos,"integer required");
      }
      return Expty(NULL,Ty_Int());
    }
    return Expty(NULL,Ty_Int());
  }
  case A_callExp:{
    E_enventry entry = S_look(venv,a->u.call.func);
    if(entry->kind!=E_funEntry){
      EM_error(a->pos,"No exist callee function");
    }
    Ty_tyList ty_tyList = entry->u.fun.formals;
    Ty_ty actual_ty = actualTy(entry->u.fun.result);

    A_expList args = a->u.call.args;

    while(args!=NULL&& ty_tyList!=NULL){
      A_exp exp = args->head;
      Tr_expty  tr_expty = transExp(level,venv,tenv,exp);
      Ty_ty arg_ty = actualTy(ty_tyList->head);
      Ty_ty param_ty = tr_expty->ty;

      if(!assertSameType(arg_ty,param_ty)){
        //        param_ty->kind != arg_ty->kind){
        EM_error(a->pos,"type mismatched");
      }
      /*
       *
       *
       *
       */
      args = args->tail;
      ty_tyList = ty_tyList->tail;
    }
    if(args!=NULL){
      EM_error(a->pos,"too much parameters");
    }else if(ty_tyList!=NULL){
      EM_error(a->pos,"too fewer parameters");
    }
    return Expty(NULL,actual_ty);
  }
  case A_letExp:{
    Tr_expty exp = NULL;
    A_decList d;
    S_beginScope(venv);
    S_beginScope(tenv);
    //+++++
    for(d = reformDecList(a->u.let.decs);d;d=d->tail){
      transDec(level,venv,tenv,d->head);
    }
    //+++++
    exp = transExp(level,venv,tenv,A_SeqExp(a->pos,a->u.let.body));
    S_endScope(venv);
    S_endScope(tenv);
    return exp;
  }
  case A_nilExp:{
    return Expty(NULL,Ty_Nil());
  }
  case A_recordExp:{
    A_efieldList a_efields = a->u.record.fields;
    S_symbol typ = a->u.record.typ;
    Ty_ty actual_ty = actualTy(S_look(tenv,typ));
    if(actual_ty!=NULL){
      if(actual_ty->kind!=Ty_record){
        EM_error(a->pos," is not a record");
      }
      Ty_fieldList ty_fieldList = actual_ty->u.record;
      while(a_efields!=NULL&&ty_fieldList!=NULL){
        A_efield a_efield = a_efields->head;
        Ty_field ty_field = ty_fieldList->head;
        if(a_efield->name != ty_field->name){
          EM_error(a->pos,"field-name mismatched");
        }
        Ty_ty ty_ty = transExp(level,venv,tenv,a_efield->exp)->ty;
        Ty_ty actual_fieldTy = actualTy(ty_field->ty);
        if(!assertSameType(actual_fieldTy,ty_ty)){//ty_ty->kind!=actual_fieldTy->kind){
          EM_error(a->pos,"type mismatched");
        }
        a_efields = a_efields->tail;
        ty_fieldList = ty_fieldList->tail;
      }
    }else{
      EM_error(a->pos," no exist record type");
    }
    return Expty(NULL,actual_ty);
  }
  case A_seqExp:{
    A_expList explist = a->u.seq;
    Tr_expty tr_expty = Expty(NULL,Ty_Void());
    while(explist!=NULL){
      A_exp exp = explist->head;
      tr_expty = transExp(level,venv,tenv,exp);
      explist = explist->tail;
    }
    return tr_expty;
  }
  case A_intExp:{
    return Expty(NULL,Ty_Int());
  }
  case A_stringExp:{
    return Expty(NULL,Ty_String());
  }
  case A_assignExp:{
    A_var var = a->u.assign.var;
    A_exp exp = a->u.assign.exp;
    Tr_expty var_expty = transVar(level,venv,tenv,var);
    Tr_expty exp_expty = transExp(level,venv,tenv,exp);
    if(!assertSameType(var_expty->ty,exp_expty->ty)){//var_expty->ty->kind!=exp_expty->ty->kind){
      if(var_expty->ty==NULL){
          EM_error(a->pos,"illegal variable name or filed name");
      }else{
        EM_error(a->pos,"can not assign to diffence type");
      }
    }
    return Expty(NULL,var_expty->ty);
  }
  case A_ifExp:{
    A_exp test_exp = a->u.iff.test;
    A_exp then_exp = a->u.iff.then;
    A_exp else_exp = a->u.iff.elsee;
    Tr_expty test_expty = transExp(level,venv,tenv,test_exp);
    Tr_expty then_expty = transExp(level,venv,tenv,then_exp);
    if(test_expty->ty->kind!=Ty_int){
      EM_error(a->pos,"test must be bool");
    }
    if(else_exp!=NULL){
      Tr_expty else_expty = transExp(level,venv,tenv,else_exp);
      if(!assertSameType(then_expty->ty,else_expty->ty)){
        EM_error(a->pos,"then and else must be same type");
      }
    }
    return Expty(NULL,then_expty->ty);
  }
  case A_whileExp:{
    A_exp test = a->u.whilee.test;
    Tr_expty test_expty = transExp(level,venv,tenv,test);
    if(test_expty->ty->kind!=Ty_int){
      EM_error(a->pos,"test-expr must be boolean value");
    }
    transExp(level,venv,tenv,a->u.whilee.body);
    return Expty(NULL,Ty_Nil());
  }
  case A_forExp:{
    A_exp lo = a->u.forr.lo;
    A_exp hi = a->u.forr.hi;
    Tr_expty lo_expty = transExp(level,venv,tenv,lo);
    Tr_expty hi_expty = transExp(level,venv,tenv,hi);
    if(lo_expty->ty->kind!=Ty_int||hi_expty->ty->kind!=Ty_int){
      EM_error(a->pos,"must in the range of integer");
    }
    return Expty(NULL,Ty_Nil());
  }
  case A_breakExp:{
    return Expty(NULL,Ty_Nil());
  }
  case A_arrayExp:{
    A_exp size = a->u.array.size;
    A_exp init = a->u.array.init;
    Tr_expty size_expty = transExp(level,venv,tenv,size);
    Tr_expty init_expty = transExp(level,venv,tenv,init);
    if(size_expty->ty->kind!=Ty_int){
      EM_error(a->pos,"size or array must be an integer");
    }
    Ty_ty ty_ty = actualTy(S_look(tenv,a->u.array.typ));
    if(ty_ty==NULL){
      EM_error(a->pos,"non-exist array type");
    } else {
      if(ty_ty->kind!=Ty_array){
        EM_error(a->pos,"the type must be an array");
      }else{
        Ty_ty unitTy = actualTy(ty_ty->u.array);
        if(!assertSameType(unitTy,init_expty->ty)){//}init_expty->ty->kind!=unitTy->kind){
          EM_error(a->pos,"initial value must be the type of array-unit");
        }
      }
    }
    return Expty(NULL,ty_ty);
  }
  case A_varExp:{
    A_var var = a->u.var;
    return transVar(level,venv,tenv,var);
  }
  }
  return Expty(NULL,NULL);
}
void transDec(Tr_level level,S_table venv,S_table tenv, A_dec d){
  switch(d->kind){
  case A_varDec:{
    if(d->u.var.typ==NULL){
      Tr_expty tr_expty = transExp(level,venv,tenv,d->u.var.init);
      if(!tr_expty->ty){
        EM_error(d->pos,"no illege init-expr");
      }else if(tr_expty->ty&&tr_expty->ty->kind==Ty_nil){
        EM_error(d->pos,"doesn't specify the record type");
      }else {
        Tr_access tr_access = Tr_allocLocal(level,TRUE);
        S_enter(venv,d->u.var.var,E_VarEntry(tr_access,tr_expty->ty));
      }
    }
    else{
      Ty_ty decType = actualTy(S_look(tenv,d->u.var.typ));
      Ty_ty initType = transExp(level,venv,tenv,d->u.var.init)->ty;
      if(decType == NULL){
        EM_error(d->pos,"no exist type");
      }else{
        if(initType->kind == Ty_nil && decType->kind != Ty_record){
          EM_error(d->pos,"require record-type");
        }else if(initType->kind == Ty_nil){

        }else if(!assertSameType(decType,initType)){//initType->kind != decType->kind){
          EM_error(d->pos,"require same type");
        }
        Tr_access tr_access = Tr_allocLocal(level,TRUE);
        S_enter(venv,d->u.var.var,E_VarEntry(tr_access,decType));
      }
    }
    break;
  }
  case A_functionDec:{
    A_fundecList fundecList = d->u.function;
    A_fundec fundec = NULL;
    while(fundecList!=NULL){
      fundec = fundecList->head;
      Ty_ty result_ty;
      if(fundec->result==NULL){
        result_ty = Ty_Void();
      }else{
        result_ty = S_look(tenv,fundec->result);
      }
      if(result_ty==NULL){
        EM_error(d->pos,"no exist type");
        /*
         * need fix bug
         */
      }
      Ty_tyList ty_tyList = makeFormalTyList(tenv,fundec->params);
      Temp_label temp_label =  Temp_newlabel();
      U_boolList u_boolList = NULL;






      Tr_level tr_level = Tr_newLevel(level,temp_label,u_boolList);
      S_enter(venv,fundec->name,E_FunEntry(tr_level,temp_label,ty_tyList,result_ty));
      fundecList = fundecList->tail;
    }
    fundecList = d->u.function;
    while(fundecList!=NULL){
      fundec = fundecList->head;
      S_beginScope(venv);
      E_enventry e_enventry = S_look(venv,fundec->name);
      Ty_tyList ty_tyList = e_enventry->u.fun.formals;
      Tr_accessList tr_accessList = e_enventry->u.fun.level->formals;
      A_fieldList a_fieldList = fundec->params;
      while(ty_tyList!=NULL&&a_fieldList!=NULL){
        S_enter(venv,a_fieldList->head->name,E_VarEntry(tr_accessList->head,ty_tyList->head));
        ty_tyList = ty_tyList->tail;
        a_fieldList = a_fieldList->tail;
        tr_accessList = tr_accessList->tail;
      }
      Tr_expty tr_expty = transExp(e_enventry->u.fun.level,venv,tenv,fundec->body);
      S_endScope(venv);
      if(e_enventry->u.fun.result==Ty_Void()&&!assertSameType(Ty_Void(),tr_expty->ty)){
        EM_error(d->pos,"the body of function must return none");
      }
      else if(e_enventry->u.fun.result!=Ty_Void()&&!assertSameType(actualTy(e_enventry->u.fun.result),tr_expty->ty)){
        EM_error(d->pos,"the type of return value must be the same of decl");
      }
      fundecList = fundecList->tail;
    }
    break;
  }
  case A_typeDec:{
    A_nametyList a_nametyList = d->u.type;
    while(a_nametyList!=NULL){
      S_enter(tenv,a_nametyList->head->name,Ty_Name(a_nametyList->head->name,NULL));
      a_nametyList = a_nametyList->tail;
    }
    a_nametyList = d->u.type;
    while(a_nametyList!=NULL){
      Ty_ty ty = S_look(tenv,a_nametyList->head->name);
      ty->u.name.ty = transTy(tenv,a_nametyList->head->ty);
      a_nametyList = a_nametyList->tail;
    }
    if(detectLoopRef(tenv,d->u.type)){
      fprintf(stderr,"Loop reference");
      exit(1);
    }
    break;
  }
  }
}
Ty_ty transTy(S_table tenv,A_ty a){
  switch(a->kind){
  case A_nameTy:{
    Ty_ty ty = S_look(tenv,a->u.name);
    return ty;
  }
  case A_recordTy:{
    Ty_ty ty = checked_malloc(sizeof(*ty));
    ty->kind = Ty_record;
    ty->u.record = makeFieldTyList(tenv,a->u.record);
    return ty;
  }
  case A_arrayTy:{
    Ty_ty ty_ty = checked_malloc(sizeof(*ty_ty));
    ty_ty->kind = Ty_array;
    ty_ty->u.array = S_look(tenv,a->u.array);
    return ty_ty;
  }
  }
  return NULL;
}


Ty_fieldList makeFieldTyList(S_table tenv,A_fieldList list){
  Ty_fieldList head = NULL;
  Ty_fieldList tail = NULL;
  while(list!=NULL){
    A_field field = list->head;
    if(tail!=NULL){
      tail->tail = Ty_FieldList(Ty_Field(field->name,S_look(tenv,field->typ)),NULL);
      tail = tail->tail;
    }else{
      tail = Ty_FieldList(Ty_Field(field->name,S_look(tenv,field->typ)),NULL);
      head = tail;
    }
    list = list->tail;
  }
  return head;
}

Ty_tyList makeFormalTyList(S_table tenv,A_fieldList list){
  Ty_tyList head = NULL;
  Ty_tyList tail = NULL;
  while(list!=NULL){
    A_field field = list->head;
    Ty_ty ty_ty = S_look(tenv,field->typ);
    if(tail!=NULL){
      tail->tail = Ty_TyList(ty_ty,NULL);
      tail = tail->tail;
    }else{
      tail = Ty_TyList(ty_ty,NULL);
      head = tail;
    }
    list = list->tail;
  }
  return head;
}

Tr_expty Expty(Tr_exp exp,Ty_ty ty){
  Tr_expty tr_expty = checked_malloc(sizeof(*tr_expty));
  tr_expty->exp = exp;
  tr_expty->ty = ty;
  return tr_expty;
}

bool detectLoopRef(S_table tenv,A_nametyList a_nametyList){
  while(a_nametyList!=NULL){
    BST mark = NULL;
    Ty_ty ty_ty = S_look(tenv,a_nametyList->head->name);
    while(ty_ty->kind==Ty_name&&!member(mark,ty_ty->u.name.sym)){
      mark = insert(mark,ty_ty->u.name.sym,NULL);
      ty_ty = ty_ty->u.name.ty;
    }
    if(ty_ty->kind==Ty_name&&member(mark,ty_ty->u.name.sym)){
      return TRUE;
    }
    a_nametyList = a_nametyList->tail;
  }
  return FALSE;
}
A_decList reformDecList(A_decList decList){
  A_decList varDecList_h=NULL,varDecList_t = NULL;
  A_nametyList a_nametyList_h=NULL,a_nametyList_t = NULL;
  A_fundecList a_fundecList_h=NULL,a_fundecList_t = NULL;
  A_decList a_decList = decList;
  while(a_decList!=NULL){
    A_dec a_dec = a_decList->head;
    switch(a_dec->kind){
    case A_varDec:{
      A_decList tmp = checked_malloc(sizeof(*tmp));
      tmp->head = a_dec;
      tmp->tail = NULL;
      if(varDecList_t==NULL){
        varDecList_h = varDecList_t = tmp;
      }else{
        varDecList_t->tail = tmp;
        varDecList_t = varDecList_t->tail;
      }
      break;
    }
    case A_functionDec:{
      A_fundecList p = a_dec->u.function;
      while(p!=NULL){
        A_fundecList tmp = A_FundecList(p->head,NULL);
        if(a_fundecList_t == NULL){
          a_fundecList_h = a_fundecList_t = tmp;
        }else{
          a_fundecList_t->tail = tmp;
          a_fundecList_t = a_fundecList_t->tail;
        }
        p = p->tail;
      }
      break;
    }
    case A_typeDec:{
      A_nametyList p = a_dec->u.type;
      while(p!=NULL){
        A_nametyList tmp = A_NametyList(p->head,NULL);
        if(a_nametyList_t == NULL){
          a_nametyList_h = a_nametyList_t = tmp;
        }else{
          a_nametyList_t->tail = tmp;
          a_nametyList_t = a_nametyList_t->tail;
        }
        p = p->tail;
      }
      break;
    }
    }
    a_decList = a_decList->tail;
  }
  A_dec functionDec = NULL;
  A_dec nametyList = NULL;
  if(decList->head!=NULL){
    functionDec = A_FunctionDec(decList->head->pos,a_fundecList_h);
    nametyList = A_TypeDec(decList->head->pos,a_nametyList_h);
  }
  A_decList resut = NULL;
  int step;
  for(step=2;step>=0;step--){
    switch(step){
    case 0:{
      if(a_nametyList_h!=NULL){
        resut = A_DecList(nametyList,resut);
      }
      break;
    }
    case 1:{
      if(a_fundecList_h!=NULL){
        resut = A_DecList(functionDec,resut);
      }
      break;
    }
    case 2:{
      resut = varDecList_h;
      break;
    }
    }
  }
  return resut;
}
