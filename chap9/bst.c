#include "stdio.h"
#include "util.h"
#include "bst.h"

BST tree(void* key,void* binding){
  BST tree = checked_malloc(sizeof(*tree));
  tree->key = key;
  tree->binding = binding;
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}
BST insert(BST tr,void* key,void* binding){
  if(tr==NULL){
    return tree(key,binding);
  }
  if(key==tr->key){
    tr->binding = binding;
  }
  if(key < tr->key){
    tr->left = insert(tr->left,key,binding);
  }
  if(key > tr->key){
    tr->right = insert(tr->right,key,binding);
  }
  return tr;
}
bool member(BST tr,void* key){
  if(tr==NULL){
    return FALSE;
  }
  if(key==tr->key){
    return TRUE;
  }
  if(key < tr->key){
    return member(tr->left,key);
  }
  if(key > tr->key){
    return member(tr->right,key);
  }
  return FALSE;
}
void* lookup(BST tr,void*key){
  if(tr==NULL){
    return NULL;
  }
  if(key==tr->key){
    return tr->binding;
  }
  if(key < tr->key){
    return lookup(tr->left,key);
  }
  if(key > tr->key){
    return lookup(tr->right,key);
  }
  return NULL;
}
