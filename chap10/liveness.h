typedef struct Live_moveList_ *Live_moveList;
struct Live_moveList_ {
  G_node src,det;
  Live_moveList tail;
};
Live_moveList Live_MoveList(G_node src,G_node dst,Live_moveList tail);
struct List_graph{
  G_graph graph;
  Live_moveList moves;
};
Temp_temp Live_gtemp(G_node n);
struct Live_graph Live_liveness(G_graph flow);