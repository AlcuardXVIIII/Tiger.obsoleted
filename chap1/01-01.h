#include "util.h"

typedef struct tree *T_tree;
struct tree{
  T_tree left;
  string key;
  void* binding;
  T_tree right;
};
T_tree tree(T_tree,string,void*,T_tree);
T_tree insert(string,void*,T_tree);
bool member(string,T_tree);
void* lookup(string,T_tree);
