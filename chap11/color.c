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

G_nodeList2 G_NodeList2(G_node,G_nodeList2,G_nodeList2);
Live_moveList LiveMoveList2(G_node,G_node,Live_moveList2,Live_moveList2);
G_nodeList2 precolored = NULL;
G_nodeList2 simplifyWorklist = NULL;
G_nodeList2 freezeWorklist = NULL;
G_nodeList2 spillWorklist = NULL;
G_nodeList2 spilledNodes  = NULL;
G_nodeList2 coalescedNodes = NULL;
G_nodeList2 coloredNodes = NULL;
G_nodeList2 selectStack = NULL;

static Live_moveList2 coalescedMoves = NULL;
static Live_moveList2 constraintMoves = NULL;
static Live_moveList2 frozenMoves = NULL;
static Live_moveList2 workListMoves = NULL;
static Live_moveList2 activeMoves = NULL;

void init(){
  precolored = G_NodeList2(NULL,NULL,NULL);
  simplifyWorklist = G_NodeList2(NULL,NULL,NULL);
  freezeWorklist = G_NodeList2(NULL,NULL,NULL);
}

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
static bool isEmpty1(G_nodeList2 set){
  return set==NULL;
}
static bool isEmpty2(Live_moveList2 set){
  return set==NULL;
}
static G_nodeList2 unionSet1(G_nodeList2 set1,G_nodeList2 set2){
  G_nodeList2 head = NULL,tail = NULL;
  while(set1!=NULL){
    G_nodeList2 node = G_NodeList2(set1->node,tail,NULL);
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set1 = set1->next;
  }
  while(set2!=NULL){
    G_nodeList2 node = G_NodeList2(set2->node,tail,NULL);
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set2 = set2->next;
  }
  return head;
}
static G_nodeList2 unionSet2(Live_moveList2 set1,Live_moveList2 set2){
  Live_moveList2 head = NULL,tail = NULL;
  Live_moveList2 pre = NULL;
  while(set1!=NULL){
    Live_moveList2 node = Live_MoveList2(set1->src,set1->dst,tail,NULL);
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set1 = set1->next;
  }
  while(set2!=NULL){
    Live_moveList2 node = Live_MoveList2(set2->src,set1->dst,tail,NULL);
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set2 = set2->next;
  }
  return head;
}
static void append1(G_nodeList2 set,G_nodeList2 node){
  node->pre = NULL;
  node->next = set;
  set = node;
}
static bool isContain1(G_nodeList2 set1,G_nodeList)
static void append2(Live_moveList2 set,Live_moveList2 node){
  node->pre = NULL;
  node->next = set;
  set = node;
}
static G_nodeList2 diffSet(G_nodeList2 set1,G_nodeList2 set2){

}
COL_result COL_color(G_graph ig,Temp_map inital,Temp_tempList regs){
  COL_result col_result = checked_malloc(sizeof(*col_result));
  //TODO


  return col_result;
}
