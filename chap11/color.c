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
static int* degree = NULL;
static G_nodeList2* adjList = NULL;
static int length;
static int K;
static bool* adjSet = NULL;
static TAB_table moveList = NULL;
static TAB_table alias = NULL;
static TAB_table color = NULL;
//数据结构初始化
void init(){
	moveList = TAB_empty();
	alias = TAB_emtpy();
	color = TAB_empty();
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
//创建集合中的结点
G_nodeList2 G_NodeList2(G_node2 node,G_nodeList2 pre,G_nodeList2 next){
  G_nodeList2 g_nodeList2 = checked_malloc(sizeof(*g_nodeList2));
  g_nodeList2->value = node;
  g_nodeList2->pre = pre;
  g_nodeList2->next = next;
  return g_nodeList2;
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
		node->kind == PRECOLORED;
	}
	else if (*set == simplifyWorklist){
		node->kind == SIMPLIFYWORKLIST;
	}
	else if (*set == freezeWorklist){
		node->kind == FREEZEWORKLIST;
	}
	else if (*set == spillWorklist){
		node->kind == SPILLWORKLIST;
	}
	else if (*set == spilledNodes){
		node->kind == SPILLEDNODES;
	}
	else if (*set == coalescedNodes){
		node->kind == COALESCEDNODES;
	}
	else if (*set == coloredNodes){
		node->kind == COLOREDNODES;
	}
	else if (*set == selectStack){
		node->kind == SELECTSTACK;
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
	while (set != NULL){
		if (set->value == node){
			return TRUE;
		}
		set = set->next;
	}
	return FALSE;
}
static bool isContain2(Live_moveList2 set, Live_moveList2node node){
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
static G_node2 peek1(G_nodeList2* set){
	if (*set != NULL){
		G_node2 node = (*set)->value;
		delete1(set, node);
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
			append1(adjList[m], node2);
		}
		if (node2->kind != PRECOLORED){
			append1(adjList[n], node1);
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
			append1(spillWorklist, g_node2);
		}
		else if (moveRelated(g_node2)){
			append1(freezeWorklist, g_node2);
		}
		else{
			append1(simplifyWorklist, g_node2);
		}
		initial = initial->next;
	}
}
static G_nodeList2 adjacent(G_node2 node){
	return diffSet1(adjList[node->node->mykey], unionSet1(selectStack, coalescedNodes));
}
static void Simplify(){
	if (simplifyWorklist != NULL){
		G_node2 node = peek1(simplifyWorklist);
		push(selectStack, node);
		G_nodeList2 g_nodeList = adjacent(node);
		while (g_nodeList != NULL){
			decrement(g_nodeList->value);
			g_nodeList = g_nodeList->next;
		}
	}
}
static void decrement(G_node2 node){
	int d = degree[node->node->mykey];
	degree[node->node->mykey]--;
	if (d == K){
		enableMoves(unionSet1(adjacent(node), G_NodeList2(node, NULL, NULL)));
		delete1(spillWorklist, node);
		if (moveRelated(node)){
			append1(freezeWorklist, node);
		}
		else{
			append1(simplifyWorklist, node);
		}
	}
}
static void enableMoves(G_nodeList2 g_nodeList2){
	while (g_nodeList2 != NULL){
		Live_moveList2 live_moveList2 = NodeMoves(g_nodeList2->value);
		while (live_moveList2 != NULL){
			if (live_moveList2->value->kind == ACTIVEMOVES){
				delete2(activeMoves, live_moveList2->value);
				append2(worklistMoves, live_moveList2->value);
			}
			live_moveList2 = live_moveList2->next;
		}
		g_nodeList2 = g_nodeList2->next;
	}
}
COL_result COL_color(G_graph ig,Temp_map inital,Temp_tempList regs){
  COL_result col_result = checked_malloc(sizeof(*col_result));
  //TODO


  return col_result;
}
