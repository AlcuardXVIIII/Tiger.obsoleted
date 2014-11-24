#include <stdio.h>
#include <assert.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "assem.h"

static AS_instrList iList = NULL,last = NULL;
static void emit(AS_instr inst);
AS_instrList F_codegen(F_frame f,T_stmList stmList);
static Temp_temp munchExp(T_exp e);
static void munchStm(T_stm s);
static Temp_tempList L(Temp_temp h,Temp_tempList t);
static void emit(AS_instr inst){
  if(last!=NULL){
    last = last->tail = AS_InstrList(inst,NULL);
  }else{
    last = iList = AS_InstrList(inst,NULL);
  }
}
AS_instrList F_codegen(F_frame f,T_stmList stmList){
  AS_instrList list;
  T_stmList sl;
  for(sl=stmList;sl;sl=sl->tail){
    munchStm(sl->head);
  }
  list = iList;
  iList = last = NULL;
  return list;
}
static Temp_temp munchExp(T_exp e){
  Temp_temp r = Temp_newtemp();
  switch(e->kind){
  case T_MEM:{
    if(e->u.MEM->kind==T_BINOP&&e->u.MEM->u.BINOP.op==T_plus){
      //T_MEM(T_BINOP(...))
      if(e->u.MEM->u.BINOP.right->kind==T_CONST){
        //T_MEM(T_BINOP(+,e1,T_CONST d))
        T_exp e1 = e->u.MEM->u.BINOP.left;
        string instr = string_format("movl %d(`s0),`d0\n",e->u.MEM->u.BINOP.right->u.CONST);
        emit(AS_Move(instr,L(r,NULL),L(munchExp(e1),NULL)));
      }else if(e->u.MEM->u.BINOP.left->kind==T_CONST){
        //T_MEM(T_BINOP(+,T_CONST d,e1))
        T_exp e1 = e->u.MEM->u.BINOP.right;
        string instr = string_format("movl %d(`s0),`d0\n",e->u.MEM->u.BINOP.left->u.CONST);
        emit(AS_Move(instr,L(r,NULL),L(munchExp(e1),NULL)));
      }else{
        assert(0);
      }
    }else if(e->u.MEM->kind==T_CONST){
      //T_MEM(T_CONST d),but this situation this will not appear
      //      string instr = string_format("movl (%0x%x),`d0\n",e->u.MEM->u.CONST);
      //      emit(AS_Move(instr,L(r,NULL),NULL));
      assert(0);
    }else{
      //T_MEM(e)
      //e maybe T_Binop(T_plus,T_Mem(T_Binop(T_PLUS,e,T_Const)),T_Binop(T_mul,...)))
      //or T_TEMP(e')
      //
      string instr = string_format("movl `s0,`d0\n");
      emit(AS_Move(instr,L(r,NULL),L(munchExp(e->u.MEM),NULL)));
    }
  }
  case T_CONST:{
    string instr = string_format("movl $%d,`d0\n",e->u.CONST);
    emit(AS_Move(instr,L(r,NULL),NULL));
  }
  case T_CALL:{
    //TODO
  }
  case T_NAME:{
    //TODO
  }
  case T_TEMP:{
    return e->u.TEMP;
  }
  case T_ESEQ:{
    assert(0);
  }
  case T_BINOP:{
    string op,sign;
    switch(e->u.BINOP.op){
    case T_plus: {op = "addl";sign="+";break;}
    case T_minus:{op = "subl";sign="-";break;}
    case T_mul:  {op = "mul"; sign="*";break;}
    case T_div:  {op = "div"; sign="/";break;}
    default:
      assert(0&&"unsupported operator now");
    }
    if(e->u.BINOP.right->kind==T_CONST){
      string instr = string_format("%s `d0,`s0%s%d\n",op,sign,e->u.BINOP.right->u.CONST);
      emit(AS_Oper(instr,L(r,NULL),L(munchExp(e->u.BINOP.left),NULL),NULL));
    }else if(e->u.BINOP.left->kind==T_CONST){
      string instr = string_format("%s `d0,`s0%s%d\n",op,sign,e->u.BINOP.left->u.CONST);
      emit(AS_Oper(instr,L(r,NULL),L(munchExp(e->u.BINOP.right),NULL),NULL));
    }else{
      string instr = string_format("%s `d0,`s0\n");
      emit(AS_Oper(instr,L(r,NULL),L(munchExp(e->u.BINOP.left),L(munchExp(e->u.BINOP.right),NULL)),NULL));
    }
  }
  }
  assert(0);
}

static void munchStm(T_stm s){
  switch(s->kind){
  case T_EXP:{
    munchExp(s->u.EXP);break;
  }
  case T_MOVE:{
    T_exp dst = s->u.MOVE.dst;
    T_exp src = s->u.MOVE.src;
    if(dst->kind==T_MEM){
      if(dst->u.MEM->kind==T_BINOP&&dst->u.MEM->u.BINOP.op==T_plus){
        if(dst->u.MEM->u.BINOP.right->kind==T_CONST){
          string instr = string_format("movl `s0,%d(`s1)\n",dst->u.MEM->u.BINOP.right->u.CONST);
          emit(AS_Move(instr,NULL,L(munchExp(src),L(munchExp(dst->u.MEM->u.BINOP.left),NULL))));
        }else if(dst->u.MEM->u.BINOP.left->kind==T_CONST){
          string instr = string_format("movl `s0,%d(`s1)\n",dst->u.MEM->u.BINOP.left->u.CONST);
          emit(AS_Move(instr,NULL,L(munchExp(src),L(munchExp(dst->u.MEM->u.BINOP.right),NULL))));
        }else{
          assert(0);
        }
      }else if(dst->u.MEM->kind==T_CONST){
        string instr = string_format("movl `s0,$%d\n",dst->u.MEM->u.CONST);
        emit(AS_Move(instr,NULL,L(munchExp(src),NULL)));
      }else if(src->kind==T_MEM){
        string instr = string_format("movl `s0,`s1\n");
        emit(AS_Move(instr,NULL,L(munchExp(src->u.MEM),L(munchExp(dst->u.MEM),NULL))));
      }else{
        string instr = string_format("movl `s0,`s1\n");
        emit(AS_Move(instr,NULL,L(munchExp(src),L(munchExp(dst->u.MEM),NULL))));
      }
    }else if(dst->kind==T_TEMP){
      string instr = string_format("movl `s0,`d0\n");
      emit(AS_Move(instr,L(dst->u.TEMP,NULL),L(src,NULL)));
    }
  }
  case T_CJUMP:{

  }
  case T_JUMP:{

  }
  case T_LABEL:{

  }
  case T_SEQ:{

  }
  default:
    break;
  }
}

static Temp_tempList L(Temp_temp h,Temp_tempList t){
  return Temp_TempList(h,t);
}
