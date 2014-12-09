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

static G_nodeList2 precolored = NULL;
static G_nodeList2 simplifyWorklist = NULL;
static G_nodeList2 freezeWorklist = NULL;
static G_nodeList2 spillWorklist = NULL;
static G_nodeList2 spilledNodes  = NULL;
static G_nodeList2 coalescedNodes = NULL;
static G_nodeList2 coloredNodes = NULL;
static G_nodeList2 selectStack = NULL;

static Live_moveList2 coalescedMoves = NULL;
static Live_moveList2 constraintMoves = NULL;
static Live_moveList2 frozenMoves = NULL;
static Live_moveList2 workListMoves = NULL;
static Live_moveList2 activeMoves = NULL;

static int* degree = NULL;
static G_nodeList2* adjList = NULL;
static int n;
static bool* adjSet = NULL;
void initAdjSet(int n){
  adjSet = checked_malloc(n*n*sizeof(bool));
  int i;
  for(i=0;i<n*n;i++){
    adjSet[i] = FALSE;
  }
}
void initAdjList(int n){
  adjList = checked_malloc(n*sizeof(G_nodeList2));
  int i;
  for(i = 0;i < n;i++){
    adjList[i] = NULL;
  }
}
void initDegree(int n){
  degree = checked_malloc(n*sizeof(int));
  int i;
  for(i = 0;i < n;i++){
    degree[i] = 0;
  }
}
void decDegree(int i){
  degree[i]++;
}
void incDegree(int i){
  degree[i]--;
  assert(degree[i]>=0);
}

G_nodeList2 G_NodeList2(G_node node,G_nodeList2 pre,G_nodeList2 next){
  G_nodeList2 g_nodeList2 = checked_malloc(sizeof(*g_nodeList2));
  g_nodeList2->node = node;
  g_nodeList2->kind = OTHER;
  g_nodeList2->pre = pre;
  g_nodeList2->next = next;
  return g_nodeList2;
}
Live_moveList2 Live_MoveList2(G_node src,G_node dst,Live_moveList2 pre,Live_moveList2 next){
  Live_moveList2 live_moveList2 = checked_malloc(sizeof(*live_moveList2));
  live_moveList2->src = src;
  live_moveList2->dst = dst;
  live_moveList2->pre = pre;
  live_moveList2->next = next;
  return live_moveList2;
}

static setSimplify(G_nodeList2 g_nodeList2){
  assert(g_nodeList2);
  g_nodeList2->kind = SIMPLIFY;
}
static setSpill(G_nodeList2 g_nodeList2){
  assert(g_nodeList2);
  g_nodeList2->kind = SPILL;
}
static setFreeze(G_nodeList2 g_nodeList2){
  assert(g_nodeList2);
  g_nodeList2->kind = FREEZE;
}
static setOther(G_nodeList2 g_nodeList2){
  assert(g_nodeList2);
  g_nodeList2->kind = OTHER;
}
static setCoalesced(Live_moveList2 live_moveList2){
  live_moveList2->kind = COALESCED;
}
static setConstraint(Live_moveList2 live_moveList2){
  live_moveList2->kind = CONSTRAINT;
}
static setFrozen(Live_moveList2 live_moveList2){
  live_moveList2->kind = FROZEN;
}
static setWorkList(Live_moveList2 live_moveList2){
  live_moveList2->kind = WORKLIST;
}
static setActive(Live_moveList2 live_moveList2){
  live_moveList2->kind = ACTIVE;
}
COL_result COL_color(G_graph ig,Temp_map inital,Temp_tempList regs){
  COL_result col_result = checked_malloc(sizeof(*col_result));
  //TODO


  return col_result;
}
