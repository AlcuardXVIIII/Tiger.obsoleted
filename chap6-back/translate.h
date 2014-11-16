typedef struct Tr_access_ *Tr_access;
typedef struct Tr_accessList_ *Tr_accessList;
typedef struct Tr_level_ *Tr_level;


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
