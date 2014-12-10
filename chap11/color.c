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
//传送指令结合的数据结构
static Live_moveList2 coalescedMoves = NULL;
static Live_moveList2 constraintMoves = NULL;
static Live_moveList2 frozenMoves = NULL;
static Live_moveList2 workListMoves = NULL;
static Live_moveList2 activeMoves = NULL;
//其他数据结构
static int* degree = NULL;
static G_nodeList2* adjList = NULL;
static int n;
static bool* adjSet = NULL;
static TAB_table moveList = NULL;
static TAB_table alias = NULL;
static TAB_table color = NULL;
//数据结构初始化
void init(){
	precolored = G_NodeList2(NULL,NULL,NULL);
	precolored->kind = PRECOLORED;	
	simplifyWorklist = G_NodeList2(NULL,NULL,NULL);
	simplifyWorklist->kind = SIMPLIFYWORKLIST;
	freezeWorklist = G_NodeList2(NULL,NULL,NULL);
	freezeWorklist->kind = FREEZEWORKLIST;
	spillWorklist = G_NodeList2(NULL, NULL, NULL);
	spillWorklist->kind = SPILLWORKLIST;
	spilledNodes = G_NodeList2(NULL, NULL, NULL);
	spilledNodes->kind = SPILLEDNODES;
	coalescedNodes = G_NodeList2(NULL, NULL, NULL);
	coalescedNodes->kind = COALESCEDNODES;
	coloredNodes = G_NodeList2(NULL, NULL, NULL);
	coloredNodes->kind = COLOREDNODES;
	selectStack = G_NodeList2(NULL, NULL, NULL);
	selectStack->kind = SELECTSTACK;
	coalescedMoves = Live_MoveList2(NULL, NULL, NULL, NULL);
	coalescedMoves->kind = COALESCEDMOVES;
	frozenMoves = Live_MoveList2(NULL, NULL, NULL, NULL);
	frozenMoves->kind = FROZENMOVES;
	workListMoves = Live_MoveList2(NULL, NULL, NULL, NULL);
	workListMoves->kind = WORKLISTMOVES;
	activeMoves = Live_MoveList2(NULL, NULL, NULL, NULL);
	activeMoves->kind = ACTIVEMOVES;
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
G_nodeList2 G_NodeList2(G_node node,G_nodeList2 pre,G_nodeList2 next){
  G_nodeList2 g_nodeList2 = checked_malloc(sizeof(*g_nodeList2));
  g_nodeList2->node = node;
  g_nodeList2->pre = pre;
  g_nodeList2->next = next;
  g_nodeList2->kind = DEFAULT1;
  return g_nodeList2;
}
Live_moveList2 Live_MoveList2(G_node src,G_node dst,Live_moveList2 pre,Live_moveList2 next){
  Live_moveList2 live_moveList2 = checked_malloc(sizeof(*live_moveList2));
  live_moveList2->src = src;
  live_moveList2->dst = dst;
  live_moveList2->pre = pre;
  live_moveList2->next = next;
  live_moveList2->kind = DEFAULT1;
  return live_moveList2;
}
//判断集合是否为空
static bool isEmpty1(G_nodeList2 set){
  return set==NULL;
}
static bool isEmpty2(Live_moveList2 set){
  return set==NULL;
}
//返回一个新的集合，次链表包含集合1和集合2的所有元素
static G_nodeList2 unionSet1(G_nodeList2 set1,G_nodeList2 set2){
  G_nodeList2 head = NULL,tail = NULL;
  while(set1!=NULL){
    G_nodeList2 node = G_NodeList2(set1->node,tail,NULL);
	node->kind = DEFAULT1;
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set1 = set1->next;
  }
  while(set2!=NULL){
    G_nodeList2 node = G_NodeList2(set2->node,tail,NULL);
	node->kind = DEFAULT1;
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
	node->kind = DEFAULT2;
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set1 = set1->next;
  }
  while(set2!=NULL){
    Live_moveList2 node = Live_MoveList2(set2->src,set1->dst,tail,NULL);
	node->kind = DEFAULT2;
    if(tail==NULL){
      head = tail = node;
    }else{
      tail = tail->next = node;
    }
    set2 = set2->next;
  }
  return head;
}
//向集合中添加新的元素
static void append1(G_nodeList2 set,G_nodeList2 node){
	/*
	 * head----->node1<------->node2<----->node3
	 */
	node->pre = NULL;
	if (set->next != NULL){
		set->next->pre = node;
	}
	node->next = set->next;
	set->next = node;
	node->kind = set->kind;
}
static void append2(Live_moveList2 set,Live_moveList2 node){
	/*
	 * head----->node1<------->node2<----->node3
	 */
	node->pre = NULL;
	if (set->next != NULL){
		set->next->pre = node;
	}
	node->next = set->next;
	set->next = node;
}
//判断集合是否包含某元素
static bool isContain1(G_nodeList2 set, G_node node){
	while (set != NULL){
		if (set->node == node){
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
		if (!isContain1(set2, set1->node)){
			if (tail == NULL){
				head = tail = G_NodeList2(set1->node, NULL, NULL);
			}
			else{
				G_nodeList2 node = G_NodeList2(set1->node, tail, NULL);
				tail = tail->next = node;
			}
		}
		set1 = set1->next;
	}
	return head;
}
//从集合中删除某个结点，并返回该结点
static G_nodeList2 delete1(G_nodeList2 set, G_node node){
	while (set != NULL){
		if (set->node == node){
			set->pre->next = set->next;
			if (set->next != NULL){
				set->next->pre = set->pre;
			}
			return set;
		}
		set = set->next;
	}
	return NULL;
}
COL_result COL_color(G_graph ig,Temp_map inital,Temp_tempList regs){
  COL_result col_result = checked_malloc(sizeof(*col_result));
  //TODO


  return col_result;
}
