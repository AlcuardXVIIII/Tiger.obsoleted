/*
 * color.h - Data structures and function prototypes for coloring algorithm
 *             to determine register allocation.
 */
typedef struct COL_result_ *COL_result;
typedef struct G_nodeList2_ *G_nodeList2;
typedef struct Live_moveList2_ *Live_moveList2;

struct COL_result_ {Temp_map coloring; Temp_tempList spills;};
COL_result COL_color(G_graph ig, Temp_map initial, Temp_tempList regs);
struct G_nodeList2_{
  G_node node;
  G_nodeList2 pre;
  G_nodeList2 next;
  enum{SIMPLIFY,SPILL,FREEZE,OTHER}kind;
};
G_nodeList2 G_NodeList2(G_node node,G_nodeList2 pre,G_nodeList2 next);
struct Live_moveList2_{
  G_node src,dst;
  enum{COALESCED,CONSTRAINT,FROZEN,WORKLIST,ACTIVE}kind;
  Live_moveList2 pre;
  Live_moveList2 next;
};
Live_moveList2 Live_MoveList2(G_node src,G_node dst,Live_moveList2 pre,Live_moveList2 next);

