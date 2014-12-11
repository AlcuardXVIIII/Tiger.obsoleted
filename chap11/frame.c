#include <stdio.h>
#include "util.h"
#include "table.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "assem.h"
#include "frame.h"
#include "codegen.h"

Temp_temp F_EAX(){
  static Temp_temp eax;
  if(eax==NULL){
    eax = Temp_newtemp();
  }
  return eax;
}
Temp_temp F_EBX(){
  static Temp_temp ebx;
  if(ebx==NULL){
    ebx = Temp_newtemp();
  }
  return ebx;
}
Temp_temp F_ECX(){
  static Temp_temp ecx;
  if(ecx==NULL){
    ecx = Temp_newtemp();
  }
  return ecx;
}
Temp_temp F_EDX(){
  static Temp_temp edx;
  if(edx==NULL){
    edx = Temp_newtemp();
  }
  return edx;
}
Temp_temp F_EDI(){
  static Temp_temp edi;
  if(edi==NULL){
    edi = Temp_newtemp();
  }
  return edi;
}
Temp_temp F_ESI(){
  static Temp_temp esi;
  if(esi==NULL){
    esi = Temp_newtemp();
  }
  return esi;
}
Temp_temp F_EBP(){
  static Temp_temp ebp;
  if(ebp==NULL){
    ebp = Temp_newtemp();
  }
  return ebp;
}
Temp_temp F_ESP(){
  static Temp_temp esp;
  if(esp==NULL){
    esp = Temp_newtemp();
  }
  return esp;
}
Temp_tempList F_registers(){
	static Temp_tempList registers = NULL;
	if (registers == NULL){
		registers = Temp_TempList(F_EAX(),
			Temp_TempList(F_EBX(),
			Temp_TempList(F_ECX(),
			Temp_TempList(F_EDX(),
			Temp_TempList(F_ESI(),
			Temp_TempList(F_EDI(),
			Temp_TempList(F_ESP(),
			Temp_TempList(F_EBP(), NULL))))))));
	}
	return registers;
}
Temp_map F_temp2Name(){
  static Temp_map temp2map = NULL;
  if(temp2map==NULL){
    temp2map = Temp_layerMap(Temp_empty(),Temp_name());
	Temp_enter(Temp_name(), F_EAX(), "%eax");
	Temp_enter(Temp_name(), F_EBX(), "%ebx");
	Temp_enter(Temp_name(), F_ECX(), "%ecx");
	Temp_enter(Temp_name(), F_EDX(), "%edx");
	Temp_enter(Temp_name(), F_ESI(), "%esi");
	Temp_enter(Temp_name(), F_EDI(), "%edi");
	Temp_enter(Temp_name(), F_ESP(), "%esp");
	Temp_enter(Temp_name(), F_EBP(), "%ebp");
  }
  return temp2map;
}
Temp_map F_precolored(){
	Temp_map initial = Temp_layerMap(Temp_empty(), Temp_name());
	return initial;
}
Temp_temp F_FP(){
  return F_EBP();
}
Temp_temp F_RV(){
  /*  static Temp_temp temp_RV = NULL;
  if(temp_RV==NULL){
    temp_RV = Temp_newtemp();
  }
  return temp_RV;*/
  return F_EAX();
}
Temp_tempList F_callee_saves(){
  static Temp_tempList temp_tempList = NULL;
  if(temp_tempList==NULL){
    temp_tempList = Temp_TempList(F_EAX(),Temp_TempList(F_EBX(),Temp_TempList(F_ECX(),Temp_TempList(F_EDI(),Temp_TempList(F_ESI(),NULL)))));
  }
  return temp_tempList;
}
Temp_tempList F_caller_saves(){
  return Temp_TempList(F_RV(),NULL);
}
F_accessList F_AccessList(F_access head,F_accessList tail){
  F_accessList f_accessList = checked_malloc(sizeof(*f_accessList));
  f_accessList->head = head;
  f_accessList->tail = tail;
  return f_accessList;
}
F_access InFrame(int offset){
  F_access f_access = checked_malloc(sizeof(*f_access));
  f_access->kind = inFrame;
  f_access->u.offset = offset;
  return f_access;
}
F_access InReg(Temp_temp reg){
  F_access f_access = checked_malloc(sizeof(*f_access));
  f_access->kind = inReg;
  f_access->u.reg = reg;
  return f_access;
}
F_frame F_newFrame(Temp_label name,U_boolList formals){
  F_frame f_frame = checked_malloc(sizeof(*f_frame));
  f_frame->name = name;
  F_accessList f_accessList_h=NULL,f_accessList_t = NULL;
  int offset = 1;
  while(formals!=NULL){
    F_access f_access = NULL;
    if(formals->head){
      f_access = InFrame(offset++);
    }else{
      f_access = InReg(Temp_newtemp());
    }
    F_accessList tmp = F_AccessList(f_access,NULL);
    if(f_accessList_t==NULL){
      f_accessList_h = f_accessList_t = tmp;
    }else{
      f_accessList_t->tail = tmp;
      f_accessList_t = f_accessList_t->tail;
    }
    formals = formals->tail;
  }
  f_frame->max_offset = 0;
  f_frame->formals = f_accessList_h;
  return f_frame;
}
F_access F_allocLocal(F_frame f,bool escape){
  F_access f_access = NULL;
  if(escape){
    f_access = InFrame(--f->max_offset);
  }else{
    f_access = InReg(Temp_newtemp());
  }
  return f_access;
}


const int F_wordSize = 4;

T_exp F_Exp(F_access f_access,T_exp framePtr){
  assert(f_access!=NULL);
  if(f_access->kind==inFrame){
    T_exp t_exp = T_Mem(T_Binop(T_plus,framePtr,T_Const(f_access->u.offset*F_wordSize)));
    return t_exp;
  }else{
    return T_Temp(f_access->u.reg);
  }
}
T_exp F_externalCall(string str,T_expList args){
  return T_Call(T_Name(Temp_namedlabel(str)),args);
}
F_frag F_StringFrag(Temp_label label,string str){
  F_frag f_frag = checked_malloc(sizeof(*f_frag));
  f_frag->kind = F_stringFrag;
  f_frag->u.stringg.str = str;
  f_frag->u.stringg.label = label;
  return f_frag;
}
F_frag F_ProcFrag(T_stm body,F_frame frame){
  F_frag f_frag = checked_malloc(sizeof(*f_frag));
  f_frag->kind = F_procFrag;
  f_frag->u.proc.body = body;
  f_frag->u.proc.frame = frame;
  return f_frag;
}
F_fragList F_FragList(F_frag head,F_fragList tail){
  F_fragList f_fragList = checked_malloc(sizeof(*f_fragList));
  f_fragList->head = head;
  f_fragList->tail = tail;
  return f_fragList;
}
void AS_instrListAppend(AS_instrList as_instrList1,AS_instrList as_instrList2){
  if(as_instrList1==NULL) return;
  AS_instrList p = as_instrList1;
  while(p->tail!=NULL){p=p->tail;}
  p->tail = as_instrList2;
}
AS_instrList procEntryExit(F_frame f,AS_instrList as_instrList){
  assert(as_instrList&&as_instrList->head->kind==I_LABEL);
  AS_instr as_instr_0 = as_instrList->head;
  as_instrList = as_instrList->tail;
  string instr_1 = string_format("    pushl `s0\n");
  string instr_2 = string_format("    movl `s0,`d0\n");
  string instr_3 = string_format("    subl $%d,`s0\n",-f->max_offset*F_wordSize);
  string instr_4 = string_format("    movl `s0,`d0\n");
  string instr_5 = string_format("    popl `d0\n");
  string instr_6 = string_format("    ret\n");
  AS_instr as_instr_1 = AS_Oper(instr_1,NULL,Temp_TempList(F_EBP(),NULL),NULL);
  AS_instr as_instr_2 = AS_Move(instr_2,Temp_TempList(F_EBP(),NULL),Temp_TempList(F_ESP(),NULL));
  AS_instr as_instr_3 = AS_Oper(instr_3,NULL,Temp_TempList(F_ESP(),NULL),NULL);
  AS_instr as_instr_4 = AS_Move(instr_4,Temp_TempList(F_ESP(),NULL),Temp_TempList(F_EBP(),NULL));
  AS_instr as_instr_5 = AS_Oper(instr_5,Temp_TempList(F_EBP(),NULL),NULL,NULL);
  AS_instr as_instr_6 = AS_Oper(instr_6,NULL,NULL,NULL);
  AS_instrListAppend(as_instrList,
                     AS_InstrList(as_instr_4,
                                  AS_InstrList(as_instr_5,
                                               AS_InstrList(as_instr_6,NULL))));
  return AS_InstrList(as_instr_0,
                      AS_InstrList(as_instr_1,
                                   AS_InstrList(as_instr_2,
                                                AS_InstrList(as_instr_3,as_instrList))));
}
