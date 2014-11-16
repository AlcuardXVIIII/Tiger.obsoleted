#include <stdio.h>
#include "01-01.h"

T_tree tree(T_tree left,string key,void* binding,T_tree right){
  T_tree t = checked_malloc(sizeof(*t));
  t->left = left;
  t->key = key;
  t->binding = binding;
  t->right = right;
}
T_tree insert(string key,void* binding,T_tree t){
  if(t==NULL){
    return tree(NULL,key,binding,NULL);
  }
  else{
    if(strcmp(key,t->key) < 0){
      return tree(insert(key,binding,t->left),t->key,t->binding,t->right);
    }
    if(strcmp(key,t->key) == 0){
      return tree(t->left,t->key,t->binding,t->right);
    }
    if(strcmp(key,t->key) > 0){
      return tree(t->left,t->key,t->binding,insert(key,binding,t->right));
    }
  }
}
bool member(string key,T_tree t){
  if(t == NULL){
    return FALSE;
  }
  if(strcmp(key,t->key) == 0)
    return TRUE;
  if(strcmp(key,t->key) < 0){
    return member(key,t->left);
  }
  else{
    return member(key,t->right);
  }
}
void* lookup(string key,T_tree t){
  if(t == NULL){
    return NULL;
  }
  if(strcmp(key,t->key) == 0)
    return t->binding;
  if(strcmp(key,t->key) < 0){
    return lookup(key,t->left);
  }
  else{
    return lookup(key,t->right);
  }
}
