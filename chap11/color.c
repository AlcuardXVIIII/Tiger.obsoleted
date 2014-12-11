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
//结点、工作表、集合和栈的数据结构
G_nodeList2 precolored = NULL;
G_nodeList2 simplifyWorklist = NULL;
G_nodeList2 freezeWorklist = NULL;
G_nodeList2 spillWorklist = NULL;
G_nodeList2 spilledNodes  = NULL;
G_nodeList2 coalescedNodes = NULL;
G_nodeList2 coloredNodes = NULL;
G_nodeList2 selectStack = NULL;
//传送指令结合的数据结构
static Live_moveList2 coalescedMoves = NULL;
static Live_moveList2 constraintMoves = NULL;
static Live_moveList2 frozenMoves = NULL;
static Live_moveList2 worklistMoves = NULL;
static Live_moveList2 activeMoves = NULL;
//其他数据结构
static int length;
static int K;
static int* degree = NULL;
static G_nodeList2* adjList = NULL;
static bool* adjSet = NULL;
static TAB_table moveList = NULL;
static TAB_table alias = NULL;
static Temp_map color = NULL;
static TAB_table G_nodeMapG_node2 = NULL;
//数据结构初始化
void init(int n, Temp_map inital,int k){
	length = n;
	K = k;
	initAdjSet(n);
	initAdjList(n);
	initDegree(n);
	moveList = TAB_empty();
	alias = TAB_emtpy();
	color = inital;
	G_nodeMapG_node2 = TAB_emtpy();
}

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
G_node2 G_Node2(G_node node){
	G_node2 g_node2 = checked_malloc(sizeof(*g_node2));
	g_node2->node = node;
	g_node2->kind = DEFAULT1;
	return g_node2;
}
//创建新的结点
G_nodeList2 G_NodeList2(G_node2 node,G_nodeList2 pre,G_nodeList2 next){
  G_nodeList2 g_nodeList2 = checked_malloc(sizeof(*g_nodeList2));
  g_nodeList2->value = node;
  g_nodeList2->pre = pre;
  g_nodeList2->next = next;
  return g_nodeList2;
}
Live_moveList2node Live_MoveList2node(Live_moveList move){
	Live_moveList2node live_moveList2node = checked_malloc(sizeof(*live_moveList2node));
	live_moveList2node->move = move;
	live_moveList2node->kind = DEFAULT2;
	return live_moveList2node;
}
Live_moveList2 Live_MoveList2(Live_moveList2node value, Live_moveList2 pre, Live_moveList2 next){
  Live_moveList2 live_moveList2 = checked_malloc(sizeof(*live_moveList2));
  live_moveList2->value = value;
  live_moveList2->pre = pre;
  live_moveList2->next = next;
  return live_moveList2;
}
//判断集合是否为空
static bool isEmpty1(G_nodeList2 set){
  return set==NULL;
}
static bool isEmpty2(Live_moveList2 set){
  return set==NULL;
}
//返回一个新的集合，此集合包含集合1和集合2的所有元素
static G_nodeList2 unionSet1(G_nodeList2 set1,G_nodeList2 set2){
  G_nodeList2 head = NULL,tail = NULL;
  while(set1!=NULL){
    G_nodeList2 node = G_NodeList2(set1->value,tail,NULL);
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set1 = set1->next;
  }
  while(set2!=NULL){
    G_nodeList2 node = G_NodeList2(set2->value,tail,NULL);
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set2 = set2->next;
  }
  return head;
}
static Live_moveList2 unionSet2(Live_moveList2 set1, Live_moveList2 set2){
	Live_moveList2 head = NULL, tail = NULL;
	while (set1 != NULL){
		Live_moveList2 node = Live_MoveList2(set1->value, tail, NULL);
		if (tail == NULL){
			head = tail = node;
		}
		else{
			tail = tail->next = node;
		}
		set1 = set1->next;
	}
	while (set2 != NULL){
		Live_moveList2 node = Live_MoveList2(set2->value, tail, NULL);
		if (tail == NULL){
			head = tail = node;
		}
		else{
			tail = tail->next = node;
		}
		set2 = set2->next;
	}
	return head;
}
//向集合中添加新的元素
static void append1(G_nodeList2* set,G_node2 node){
	/*
	 * node<------->(node2<----->node1)==set
	 */
	if (*set == precolored){
		node->kind = PRECOLORED;
	}
	else if (*set == simplifyWorklist){
		node->kind = SIMPLIFYWORKLIST;
	}
	else if (*set == freezeWorklist){
		node->kind = FREEZEWORKLIST;
	}
	else if (*set == spillWorklist){
		node->kind = SPILLWORKLIST;
	}
	else if (*set == spilledNodes){
		node->kind = SPILLEDNODES;
	}
	else if (*set == coalescedNodes){
		node->kind = COALESCEDNODES;
	}
	else if (*set == coloredNodes){
		node->kind = COLOREDNODES;
	}
	else if (*set == selectStack){
		node->kind = SELECTSTACK;
	}
	G_nodeList2 g_nodeList2 = G_NodeList2(node, NULL, NULL);
	if (*set == NULL){
		*set = g_nodeList2;
	}
	else{
		(*set)->pre = g_nodeList2;
		g_nodeList2->next = (*set);
		(*set) = g_nodeList2;
	}
}
static void append2(Live_moveList2* set, Live_moveList2node node){
	/*
	* node<------->(node2<----->node1)==set
	*/
	if (*set == coalescedMoves){
		node->kind = COALESCEDMOVES;
	}
	else if (*set == constraintMoves){
		node->kind = CONSTRAINTMOVES;
	}
	else if (*set == frozenMoves){
		node->kind = FROZENMOVES;
	}
	else if (*set == worklistMoves){
		node->kind = WORKLISTMOVES;
	}
	else if (*set == activeMoves){
		node->kind = ACTIVEMOVES;
	}
	Live_moveList2 live_moveList2 = Live_MoveList2(node, NULL, NULL);
	if (*set == NULL){
		*set = live_moveList2;
	}
	else{
		(*set)->pre = live_moveList2;
		live_moveList2->next = (*set);
		(*set) = live_moveList2;
	}
}
//判断集合是否包含某元素
static bool isContain1(G_nodeList2 set, G_node2 node){

	if (set == precolored){
		return node->kind == PRECOLORED;
	}
	else if (set == simplifyWorklist){
		return node->kind == SIMPLIFYWORKLIST;
	}
	else if (set == freezeWorklist){
		return node->kind == FREEZEWORKLIST;
	}
	else if (set == spillWorklist){
		return node->kind == SPILLWORKLIST;
	}
	else if (set == spilledNodes){
		return node->kind == SPILLEDNODES;
	}
	else if (set == coalescedNodes){
		return node->kind == COALESCEDNODES;
	}
	else if (set == coloredNodes){
		return node->kind == COLOREDNODES;
	}
	else if (set == selectStack){
		return node->kind == SELECTSTACK;
	}
	while (set != NULL){
		if (set->value == node){
			return TRUE;
		}
		set = set->next;
	}
	return FALSE;
}
static bool isContain2(Live_moveList2 set, Live_moveList2node node){
	if (set == coalescedMoves){
		return node->kind == COALESCEDMOVES;
	}
	else if (set == constraintMoves){
		return node->kind == CONSTRAINTMOVES;
	}
	else if (set == frozenMoves){
		return node->kind == FROZENMOVES;
	}
	else if (set == worklistMoves){
		return node->kind == WORKLISTMOVES;
	}
	else if (set == activeMoves){
		return node->kind == ACTIVEMOVES;
	}
	while (set != NULL){
		if (set->value == node){
			return TRUE;
		}
		set = set->next;
	}
	return FALSE;
}
//返回一个新的集合，此集合是集合1和集合2的差集
static G_nodeList2 diffSet1(G_nodeList2 set1,G_nodeList2 set2){
	G_nodeList2 head, tail;
	while (set1 != NULL){
		if (!isContain1(set2, set1->value)){
			if (tail == NULL){
				head = tail = G_NodeList2(set1->value, NULL, NULL);
			}
			else{
				G_nodeList2 node = G_NodeList2(set1->value, tail, NULL);
				tail = tail->next = node;
			}
		}
		set1 = set1->next;
	}
	return head;
}
static Live_moveList2 diffSet2(Live_moveList2 set1, Live_moveList2 set2){
	Live_moveList2 head, tail;
	while (set1 != NULL){
		if (!isContain2(set2, set1->value)){
			if (tail == NULL){
				head = tail = Live_MoveList2(set1->value, NULL, NULL);
			}
			else{
				Live_moveList2 node = Live_MoveList2(set1->value, tail, NULL);
				tail = tail->next = node;
			}
		}
		set1 = set1->next;
	}
	return head;
}
//返回一个新的集合，此集合是集合1和集合2的交集
static G_nodeList2 interSet1(G_nodeList2 set1, G_nodeList2 set2){
	G_nodeList2 head, tail;
	while (set1 != NULL){
		if (isContain1(set2, set1->value)){
			if (tail == NULL){
				head = tail = G_NodeList2(set1->value, NULL, NULL);
			}
			else{
				G_nodeList2 node = G_NodeList2(set1->value, tail, NULL);
				tail = tail->next = node;
			}
		}
		set1 = set1->next;
	}
	return head;
}
static Live_moveList2 interSet2(Live_moveList2 set1, Live_moveList2 set2){
	Live_moveList2 head, tail;
	while (set1 != NULL){
		if (isContain2(set2, set1->value)){
			if (tail == NULL){
				head = tail = Live_MoveList2(set1->value, NULL, NULL);
			}
			else{
				Live_moveList2 node = Live_MoveList2(set1->value, tail, NULL);
				tail = tail->next = node;
			}
		}
		set1 = set1->next;
	}
	return head;
}
//从集合中删除某个结点
static void delete1(G_nodeList2* set_, G_node2 node){
	assert(*set_);
	G_nodeList2 set = *set_;
	while (set != NULL){
		if (set->value == node){
			if (set->pre != NULL){
				set->pre->next = set->next;
			}
			if (set->next != NULL){
				set->next->pre = set->pre;
			}
			break;
		}
		set = set->next;
	}
	if ((*set_)->value == node){
		*set = *set->next;
	}
}
static void delete2(Live_moveList2* set_, Live_moveList2node node){
	assert(*set_);
	Live_moveList2 set = *set_;
	while (set != NULL){
		if (set->value == node){
			if (set->pre != NULL){
				set->pre->next = set->next;
			}
			if (set->next != NULL){
				set->next->pre = set->pre;
			}
			break;
		}
		set = set->next;
	}
	if ((*set_)->value == node){
		*set = *set->next;
	}
}
static G_node2 peek1(G_nodeList2* set){
	if (*set != NULL){
		G_node2 node = (*set)->value;
		delete1(set, node);
		return node;
	}
	return NULL;
}
static G_node2 pop1(G_nodeList2* stack){
	return peek1(stack);
}
static Live_moveList2node peek2(Live_moveList2* set){
	if (*set != NULL){
		Live_moveList2node node = (*set)->value;
		delete2(set, node);
		return node;
	}
	return NULL;
}
static void push(G_nodeList2* stack, G_node2 node){
	append1(stack, node);
}
static bool isLink(int m, int n){
	return adjSet[m*length + n];
}
static void addEdge_(int m,int n){
	adjSet[m*length + n] = TRUE;
}
static void addEdge(G_node2 node1, G_node2 node2){
	int m = node1->node->mykey;
	int n = node2->node->mykey;
	if (m != n&&!isLink(m,n)){
		addEdge_(m, n);
		addEdge_(n, m);
		if (node1->kind != PRECOLORED){
			append1(&adjList[m], node2);
		}
		if (node2->kind != PRECOLORED){
			append1(&adjList[n], node1);
		}
	}
}
static Live_moveList2 NodeMoves(G_node2 node){
	return interSet2(TAB_look(moveList, node), unionSet2(activeMoves, worklistMoves));
}
static bool moveRelated(G_node2 node){
	return !isEmpty1(NodeMoves(node));
}
static void makeWorklist(G_nodeList2 initial){
	while (initial != NULL){
		G_node2 g_node2 = initial->value;
		int pos = g_node2->node->mygraph;
		if (degree[pos] >= K){
			append1(&spillWorklist, g_node2);
		}
		else if (moveRelated(g_node2)){
			append1(&freezeWorklist, g_node2);
		}
		else{
			append1(&simplifyWorklist, g_node2);
		}
		initial = initial->next;
	}
}
static G_nodeList2 adjacent(G_node2 node){
	return diffSet1(adjList[node->node->mykey], unionSet1(selectStack, coalescedNodes));
}
static void simplify(){
	if (simplifyWorklist != NULL){
		G_node2 node = peek1(&simplifyWorklist);
		push(selectStack, node);
		G_nodeList2 g_nodeList = adjacent(node);
		while (g_nodeList != NULL){
			decrementDegree(g_nodeList->value);
			g_nodeList = g_nodeList->next;
		}
	}
}
static void decrementDegree(G_node2 node){
	int d = degree[node->node->mykey];
	degree[node->node->mykey]--;
	if (d == K){
		enableMoves(unionSet1(adjacent(node), G_NodeList2(node, NULL, NULL)));
		delete1(&spillWorklist, node);
		if (moveRelated(node)){
			append1(&freezeWorklist, node);
		}
		else{
			append1(&simplifyWorklist, node);
		}
	}
}
static void enableMoves(G_nodeList2 g_nodeList2){
	while (g_nodeList2 != NULL){
		Live_moveList2 live_moveList2 = NodeMoves(g_nodeList2->value);
		while (live_moveList2 != NULL){
			if (live_moveList2->value->kind == ACTIVEMOVES){
				delete2(&activeMoves, live_moveList2->value);
				append2(&worklistMoves, live_moveList2->value);
			}
			live_moveList2 = live_moveList2->next;
		}
		g_nodeList2 = g_nodeList2->next;
	}
}
static void coalesce(){
	Live_moveList2node  node = peek2(&worklistMoves);
	G_node2 x = getAlias(TAB_look(G_nodeMapG_node2, node->move->dst));
	G_node2 y = getAlias(TAB_look(G_nodeMapG_node2, node->move->src));
	G_node2 u = x;
	G_node2 v = y;
	if (isContain1(precolored, y)){
		u = y;
		v = x;
	}
	if (u == v){
		append2(&coalescedMoves, node);
		addWorkList(u);
	}
	else if (isContain1(precolored, v) || isLink(u->node->mykey,v->node->mykey)){
		append2(&constraintMoves, node);
		addWorkList(u);
		addWorkList(v);
	}
	else {
		bool bFlag = TRUE;
		if (isContain1(precolored, u)){
			G_nodeList2 g_nodeList2 = adjacent(v);
			while (g_nodeList2 != NULL){
				if (!OK(g_nodeList2->value, u)){
					bFlag = FALSE;
					break;
				}
				g_nodeList2 = g_nodeList2->next;
			}
		}
		else{
			bFlag = FALSE;
		}
		if (bFlag || !isContain1(precolored, u) && conservative(unionSet1(adjacent(u), adjacent(v)))){
			append2(&coalescedMoves, node);
			combine(u, v);
			addWorkList(u);
		}
		else{
			append2(&activeMoves, node);
		}
	}
}
static void addWorkList(G_node2 node){
	if (!isContain1(precolored,node) && !moveRelated(node) && degree[node->node->mykey] < K){
		delete1(&freezeWorklist, node);
		append1(&simplifyWorklist, node);
	}
}
static bool OK(G_node2 t, G_node2 r){
	return degree[t->node->mykey] < K || isContain1(precolored, t) || isLink(t->node->mykey, r->node->mykey);
}
static bool conservative(G_nodeList2 nodes){
	int k = 0;
	while (nodes != NULL){
		if (degree[nodes->value->node->mykey] >= K){
			k++;
		}
		nodes = nodes->next;
	}
	return k < K;
}
static G_node2 getAlias(G_node2 node){
	if (isContain1(coalescedNodes, node)){
		getAlias(TAB_look(alias, node));
	}
	else node;
}
static void combine(G_node2 u, G_node2 v){
	if (isContain1(freezeWorklist,v)){
		delete1(&freezeWorklist, v);
	}
	else{
		delete1(&spillWorklist, v);
	}
	append1(&coalescedNodes, v);
	TAB_enter(alias, v, u);
	TAB_enter(moveList,u,unionSet2(TAB_look(moveList, u), TAB_look(moveList, v)));
	enableMoves(v);
	G_nodeList2 g_nodeList2 = adjancent(v);
	while (g_nodeList2 != NULL){
		addEdge(g_nodeList2->value, u);
		decrementDegree(g_nodeList2->value);
		g_nodeList2 = g_nodeList2->next;
	}
	if (degree[u->node->mykey] >= K&&isContain1(freezeWorklist,u)){
		delete1(&freezeWorklist, u);
		append1(&spillWorklist, u);
	}
}
static void freeze(){
	G_node2 node = peek1(&freezeWorklist);
	append1(&simplifyWorklist, node);
	freezeMoves(node);
}
static void freezeMoves(G_node2 u){
	Live_moveList2 live_moveList2 = NodeMoves(u);
	while (live_moveList2 != NULL){
		Live_moveList2node m = live_moveList2->value;
		G_node2 x = TAB_look(G_nodeMapG_node2,m->move->dst);
		G_node2 y = TAB_look(G_nodeMapG_node2, m->move->src);
		G_node2 v = getAlias(y);
		if (getAlias(y) == getAlias(u)){
			v = getAlias(x);
		}
		delete2(&activeMoves, m);
		append2(&frozenMoves, m);
		if (isEmpty1(NodeMoves(v)) && degree[v->node->mykey] < K){
			delete2(&freezeWorklist, v);
			append1(&simplifyWorklist, v);
		}
		live_moveList2 = live_moveList2->next;
	}
}
static void selectSpill(){
	G_node2 m = peek1(&spillWorklist);
	append1(&simplifyWorklist, m);
	freezeMoves(m);
}
static G_nodeList2 allReg(){
	return unionSet1(precolored, NULL);
}
static void assignColors(){
	while (!isEmpty1(selectStack)){
		G_node2 n = pop(selectStack);
		G_nodeList2 okColors = allReg();
		G_nodeList2 g_nodeList2 = adjList[n->node->mykey];
		while (g_nodeList2){
			G_node2 w = g_nodeList2->value;
			if (isContain1(unionSet1(coloredNodes,precolored),getAlias(w))){
				G_node2 g_node2 = TAB_look(color, getAlias(w));
				delete1(okColors, g_node2);
			}
			g_nodeList2->next;
		}
		if (isEmpty1(okColors)){
			append1(&spilledNodes, n);
		}
		else{
			append1(&coloredNodes, n);
			TAB_enter(color, n, okColors->value);
			Temp_enter(color, n->node->info, Temp_look(color,okColors->value->node->info));
		}
	}
	G_nodeList2 g_nodeList2 = coalescedMoves;
	while (g_nodeList2 != NULL){
		Temp_enter(color, g_nodeList2->value->node->info, Temp_look(color, getAlias(g_nodeList2->value)->node->info));
		g_nodeList2 = g_nodeList2->next;
	}
}
COL_result COL_color(Live_graph ig, Temp_map inital, Temp_tempList regs){
	G_graph graph = ig->graph;
	Live_moveList moves = ig->moves;
	G_nodeList g_nodeList = G_nodes(graph);
	init(graph->nodecount, inital,lengthOfTempList(regs));
	G_nodeList2 g_nodeList2 = NULL;
	//initial precolored and G_nodeMapG_node2
	while (g_nodeList != NULL){
		G_node g_node = g_nodeList->head;
		G_node2 g_node2 = G_Node2(g_node);
		TAB_enter(G_nodeMapG_node2, g_node, g_node2);
		if (inTemp_tempList(g_node->info,regs)){
			append1(&precolored, g_node2);
		}
		else{
			append1(&g_nodeList2, g_node2);
		}
		g_nodeList = g_nodeList->tail;
	}
	g_nodeList = G_nodes(graph);
	//initial adjSet and adjList
	while (g_nodeList != NULL){
		G_node g_node = g_nodeList->head;
		G_node2 g_node2 = TAB_Look(G_nodeMapG_node2, g_node);
		G_nodeList g_nodeList = G_adj(g_node);
		while (g_nodeList != NULL){
			G_node otherG_node = g_nodeList->head;
			G_node2 otherG_node2 = TAB_Look(G_nodeMapG_node2, otherG_node);
			addEdge(g_node2, otherG_node2);
			g_nodeList = g_nodeList->tail;
		}
		g_nodeList = g_nodeList->tail;
	}
	//initial moveList and worklistMoves
	while (moves != NULL){
		Live_moveList2node live_moveList2node = Live_MoveList2node(moves);
		append2(&worklistMoves, live_moveList2node);
		G_node2 dst = TAB_look(G_nodeMapG_node2, moves->dst);
		G_node2 src = TAB_look(G_nodeMapG_node2, moves->src);
		TAB_enter(moveList, dst, unionSet2(TAB_look(moveList, dst), Live_MoveList2(live_moveList2node,NULL,NULL)));
		TAB_enter(moveList, src, unionSet2(TAB_look(moveList, src), Live_MoveList2(live_moveList2node, NULL, NULL)));
		moves = moves->tail;
	}

	makeWorklist(g_nodeList2);
	do{
		if (!isEmpty1(simplifyWorklist)){
			simplify();
		}
		else if (!isEmpty2(worklistMoves)){
			coalesce();
		}
		else if (!isEmpty1(freezeWorklist)){
			freeze();
		}
		else{
			selectSpill();
		}
	} while (!isEmpty1(simplifyWorklist)||!isEmpty2(worklistMoves)||!isEmpty1(freezeWorklist)||!isEmpty1(spillWorklist));
	assignColors();
	COL_result col_result = checked_malloc(sizeof(*col_result));
	col_result->coloring = color;
	Temp_tempList spills = NULL;
	while (spilledNodes != NULL){
		spills = Temp_TempList(spilledNodes->value->node->info,spills);
		spilledNodes = spilledNodes->next;
	}
	col_result->spills = spills;
	return col_result;
}
