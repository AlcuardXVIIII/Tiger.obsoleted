typedef struct Tr_expty_ *Tr_expty;

struct Tr_expty_{Tr_exp exp;Ty_ty ty;};

Tr_expty transVar(Tr_level level,S_table venv,S_table tenv,A_var v);
Tr_expty transExp(Tr_level level,S_table venv,S_table tenv,A_exp a);
Tr_exp transDec(Tr_level level,S_table venv,S_table tenv, A_dec d);
Ty_ty transTy(S_table tenv,A_ty a);

Ty_fieldList makeFieldTyList(S_table tenv,A_fieldList list);
Ty_tyList makeFormalTyList(S_table tenv,A_fieldList list);
Tr_expty Expty(Tr_exp exp,Ty_ty ty);
void SEM_transProg(A_exp exp);
bool assertSameType(Ty_ty expected,Ty_ty actual);
bool detectLoopRef(S_table tenv,A_nametyList a_nametyList);
A_decList reformDecList(A_decList a_decList);
