#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
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
