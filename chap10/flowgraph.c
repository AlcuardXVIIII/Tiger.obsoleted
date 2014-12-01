#include <stdio.h>
#include <assert.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "graph.h"
#include "assem.h"
#include "flowgraph.h"

Temp_tempList FG_def(G_node n){
  AS_instr as_instr = G_nodeInfo(n);
  assert(as_instr);
  switch(as_instr->kind){
  case I_OPER:
    return as_instr->u.OPER.dst;
  case I_LABEL:
    return NULL;
  case I_MOVE:
    return as_instr->u.MOVE.dst;
  default:
    assert(0);
  }
}
Temp_tempList FG_use(G_node n){
  AS_instr as_instr = G_nodeInfo(n);
  assert(as_instr);
  switch(as_instr->kind){
  case I_OPER:
    return as_instr->u.OPER.src;
  case I_LABEL:
    return NULL;
  case I_MOVE:
    return as_instr->u.MOVE.src;
  default:
    assert(0);
  }
}
bool FG_isMove(G_node n){
  AS_instr as_instr = G_nodeInfo(n);
  assert(as_instr);
  return as_instr->kind==I_MOVE;
}
G_graph FG_AssemFlowGraph(AS_instrList il){

}
