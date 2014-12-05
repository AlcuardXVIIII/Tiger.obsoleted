typedef struct BST_ *BST;
struct BST_{
  void* key;
  void* binding;
  BST left;
  BST right;
};
BST tree(void* key,void*binding);
BST insert(BST tr,void* key,void* binding);
bool member(BST tr,void* key);
void* lookup(BST tr,void* key);
