#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "assem.h"
#include "graph.h"
#include "flowgraph.h"
#include "liveness.h"
#include "color.h"
#include "tree.h"
#include "frame.h"
#include "color.h"
#include "regalloc.h"

RA_result RA_regAlloc(F_frame f,AS_instrList il){
  G_graph g_graph = FG_AssemFlowGraph(il);
  Live_graph live_graph = Live_liveness(g_graph);
  Temp_map initial = F_precolored();
  Temp_tempList regs = F_registers();

  COL_result col_result = COL_color(g_graph,initial,regs);
  if(col_result->spills!=NULL){





    il = NULL;
    return RA_regAlloc(f,il);
  }
  RA_result ra_result = checked_malloc(sizeof(*ra_result));
  ra_result->coloring = col_result->coloring;
  //TODO
  ra_result->il = il;
  return ra_result;
}
