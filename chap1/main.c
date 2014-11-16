#include <stdio.h>
#include "01-01.h"
void printTree(T_tree t){
  if(t == NULL){
    return;
  }
  printTree(t->left);
  printf(" %s ",t->key);
  printTree(t->right);
}
int main(){
  string name1 = "1",name3 = "3",name4 = "4",name8 = "8";

  T_tree t = tree(NULL,name1,(void*)(&name1),NULL);
  t = insert(name3,(void*)(&name3),t);
  t = insert(name4,(void*)(&name4),t);
  t = insert(name8,(void*)(&name8),t);
  if(member("1",t) && member("4",t) && member("8",t) && !member("2",t)){
    printf("member function is ok!\n");
  }
  void* result = lookup("555",t);
  if(result != NULL){
    printf("lookup function if ok\n");
    printf("%s\n",*((string*)result));
  }

  printTree(t);
  printf("\n");
  return 0;
}
