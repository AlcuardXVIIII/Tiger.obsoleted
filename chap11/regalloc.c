#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "table.h"
#include "assem.h"
#include "graph.h"
#include "flowgraph.h"
#include "liveness.h"
#include "color.h"
#include "tree.h"
#include "frame.h"
#include "color.h"
#include "regalloc.h"
static int getOffset(TAB_table table,F_frame f,Temp_temp temp){
	F_access f_access = TAB_look(table, temp);
	if (f_access == NULL){
		f_access = F_allocLocal(f, TRUE);
		TAB_enter(table, temp, f_access);
	} 
	return f_access->u.offset*F_wordSize;
}
static Temp_temp getNewTemp(TAB_table table, Temp_temp oldTemp){
	Temp_temp newTemp = TAB_look(table, oldTemp);
	if (newTemp == NULL){
		newTemp = Temp_newtemp();
		TAB_enter(table, oldTemp, newTemp);
	}
	return newTemp;
}
static Temp_tempList rewriteProgram(F_frame f,Temp_tempList temp_tempList,AS_instrList il){
	AS_instrList pre = NULL, cur = il;
	Temp_tempList newTempList = NULL;
	while (cur != NULL){
		AS_instr as_Instr = cur->head;
		switch (as_Instr->kind){
		case I_OPER:
		case I_MOVE:
			Temp_tempList defTempList = as_Instr->u.OPER.dst;
			Temp_tempList useTempList = as_Instr->u.OPER.src;
			TAB_table oldMapNew = TAB_empty();
			TAB_table tempMapOffset = TAB_empty();
			bool needDelete = FALSE;
			while (useTempList != NULL){
				if (inTemp_tempList(useTempList->head, temp_tempList)){
					needDelete = TRUE;
					assert(pre);
					Temp_temp newTemp = getNewTemp(oldMapNew, useTempList->head);
					if (!inTemp_tempList(newTemp, newTempList)){
						newTempList = Temp_TempList(newTemp, newTempList);
					}
					int offset = getOffset(tempMapOffset,f, newTemp);
					string instr = string_format("movl (%d),`d0\n", offset);
					AS_instr as_instr = AS_Move(instr, NULL, Temp_TempList(newTemp,NULL));
					pre = pre->tail = AS_InstrList(as_instr,cur);
				}
				useTempList = useTempList->tail;
			}
			while (defTempList != NULL){
				if (inTemp_tempList(defTempList->head, temp_tempList)){
					needDelete = TRUE;
					assert(pre);
					Temp_temp newTemp = getNewTemp(oldMapNew, defTempList->head);
					if (!inTemp_tempList(newTemp, newTempList)){
						newTempList = Temp_TempList(newTemp, newTempList);
					}
					int offset = getOffset(tempMapOffset, f, newTemp);
					string instr = string_format("movl `s0,(%d)\n", offset);
					AS_instr as_instr = AS_Move(instr, Temp_TempList(newTemp, NULL), NULL);
					cur->tail = AS_InstrList(as_instr, cur->tail);
				}
				defTempList = defTempList->tail;
			}
			if (needDelete){
				pre->tail = cur->tail;
			}
			break;
		default:
			pre = cur;
			break;
		}
		cur = cur->tail;
	}
	return newTempList;
}
RA_result RA_regAlloc(F_frame f,AS_instrList il){
  G_graph g_graph = FG_AssemFlowGraph(il);
  Live_graph live_graph = Live_liveness(g_graph);
  Temp_map initial = F_precolored();
  Temp_tempList regs = F_registers();
  COL_result col_result = COL_color(g_graph,initial,regs);
  if(col_result->spills!=NULL){
	  Temp_tempList newTempList = rewriteProgram(f, col_result->spills, il);
	  return RA_regAlloc(f,il);
  }
  RA_result ra_result = checked_malloc(sizeof(*ra_result));
  ra_result->coloring = col_result->coloring;
  ra_result->il = il;
  return ra_result;
}
