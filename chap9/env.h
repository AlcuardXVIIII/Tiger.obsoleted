typedef struct E_enventry_ *E_enventry;
typedef struct E_stack_ *E_stack;
struct E_enventry_{
  enum{E_varEntry,E_funEntry}kind;
  union{
    struct {Tr_access access;Ty_ty ty;}var;
    struct {Tr_level level;Temp_label label;Ty_tyList formals;Ty_ty result;}fun;
  }u;
};
E_enventry E_VarEntry(Tr_access access,Ty_ty ty);
E_enventry E_FunEntry(Tr_level,Temp_label label,Ty_tyList formals,Ty_ty result);
S_table E_base_tenv(void);
S_table E_base_venv(void);


struct E_stack_{
  void* object;
  E_stack next;
};

void E_push(E_stack* stack,void *object);
void E_pop(E_stack* stack);
void* E_top(E_stack stack);
E_stack E_newStack();
