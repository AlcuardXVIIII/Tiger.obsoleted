#include <stdio.h>
#include "util.h"
#include "table.h"
#include "symbol.h"
#include "temp.h"
#include "frame.h"

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
  int offset = 0;
  while(formals!=NULL){
    F_access f_access = NULL;
    if(formals->head){
      f_access = InFrame(--offset);
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
  f_frame->max_offset = offset;
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
