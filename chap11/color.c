#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "table.h"
#include "temp.h"
#include "assem.h"
#include "graph.h"
#include "flowgraph.h"
#include "liveness.h"
#include "color.h"

/*static G_nodeList precolored = NULL;
static G_nodeList simplifyWorklist = NULL;
static G_nodeList freezeWorklist = NULL;
static G_nodeList spillWorklist = NULL;
static G_nodeList spilledNodes  = NULL;
static G_nodeList coalescedNodes = NULL;
static G_nodeList coloredNodes = NULL;
static G_nodeList selectStack = NULL;

static Live_moveList coalescedMoves = NULL;
static Live_moveList constraintMoves = NULL;
static Live_moveList frozenMoves = NULL;
static Live_moveList workListMoves = NULL;
static Live_moveList activeMoves = NULL;
*/

COL_result COL_color(G_graph ig,Temp_map inital,Temp_tempList regs){
  COL_result col_result = checked_malloc(sizeof(*col_result));
  //TODO


  return col_result;
}
