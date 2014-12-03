#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "assem.h"
#include "graph.h"
#include "liveness.h"

static void enterLiveMap(G_table t,G_node flowNode,Temp_tempList temp){
  G_enter(t,flowNode,temp);
}
static Temp_tempList lookupLiveMap(G_table t,G_node flownode){
  return (Temp_tempList)G_look(t,flownode);
}
Live_moveList Live_MoveList(G_node src,G_node dst,Live_moveList tail){
  Live_moveList live_moveList = checked_malloc(sizeof(*live_moveList));
  live_moveList->src = src;
  live_moveList->dst = dst;
  live_moveList->tail = tail;
  return live_moveList;
}
Temp_temp Live_gtemp(G_node n){

}
Live_graph Live_liveness(G_graph flow){
  Live_graph live_graph = checked_malloc(sizeof(*live_graph));




  return live_graph;
}
