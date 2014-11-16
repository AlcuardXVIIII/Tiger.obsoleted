typedef struct Tr_access_ *Tr_access;
typedef struct Tr_accessList_ *Tr_accessList;
typedef struct Tr_level_ *Tr_level;
typedef struct Tr_exp_ *Tr_exp;
typedef struct patchList_ *patchList;

struct Tr_access_{
  F_access access;
  Tr_level level;
};
struct Tr_accessList_{
  Tr_access head;
  Tr_accessList tail;
};
struct Tr_level_{
  Tr_level parent;
  Temp_label name;
  F_frame frame;
  Tr_accessList formals;
};
Tr_access Tr_Access(F_access access,Tr_level level);
Tr_accessList Tr_AccessList(Tr_access head,Tr_accessList tail);
Tr_level Tr_outermost(void);
Tr_level Tr_newLevel(Tr_level parent,Temp_label name,U_boolList formals);
Tr_access Tr_allocLocal(Tr_level level,bool escape);

struct patchList_{
  Temp_label* head;
  patchList tail;
};
T_expList Tr_ExpList(Tr_exp exp,T_expList tail);
patchList PatchList(Temp_label* label,patchList tail);
void doPatch(patchList,Temp_label);
T_exp staticLink(Tr_level curLevel,Tr_level desLevel);
Tr_exp Tr_simpleVar(Tr_access tr_access,Tr_level curLevel);
Tr_exp Tr_fieldVar(Tr_exp var,int offset);
Tr_exp Tr_subscriptVar(Tr_exp var,Tr_exp index);
Tr_exp Tr_opExp(A_oper oper,Tr_exp left,Tr_exp right);
Tr_exp Tr_relExp(A_oper oper,Tr_exp left,Tr_exp right);
Tr_exp Tr_ifExp(Tr_exp test,Tr_exp thenn,Tr_exp elsee);
Tr_exp Tr_whileExp(Tr_exp test,Tr_exp body,patchList patList);
Tr_exp Tr_forExp(Tr_exp simpVar,Tr_exp lo,Tr_exp hi,Tr_exp body,patchList patList);
Tr_exp Tr_breakExp(patchList* patList);
Tr_exp Tr_callExp(S_symbol fun,T_exp staticLink,T_expList t_expList);
Tr_exp Tr_nop();
Tr_exp Tr_letExp(T_expList list);
Tr_exp Tr_recordExp(int n,T_expList t_expList);
Tr_exp Tr_arrayExp(Tr_exp size,Tr_exp init);
Tr_exp Tr_intExp(int n);
Tr_exp Tr_stringExp(string str);
Tr_exp Tr_nilExp();
Tr_exp Tr_assignExp(Tr_exp var,Tr_exp exp);
Tr_exp Tr_seqExp(T_expList t_expList);
Tr_exp Tr_eqIntExp(A_oper oper,Tr_exp left,Tr_exp right);
Tr_exp Tr_eqStringExp(A_oper oper,Tr_exp left,Tr_exp right);
Tr_exp Tr_eqRefExp(A_oper oper,Tr_exp left,Tr_exp right);
void Tr_procEntryExit(Tr_level level,Tr_exp body);
F_fragList Tr_getResult();
