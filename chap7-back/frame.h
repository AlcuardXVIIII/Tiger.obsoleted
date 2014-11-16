typedef struct F_frame_ *F_frame;
typedef struct F_access_ *F_access;
typedef struct F_accessList_ *F_accessList;
typedef struct F_frag_ *F_frag;
typedef struct F_fragList_ *F_fragList;

struct F_access_{
  enum{inFrame,inReg}kind;
  union{
    int offset;
    Temp_temp reg;
  }u;
};
struct F_accessList_{F_access head;F_accessList tail;};

struct F_frame_{
  Temp_label name;
  F_accessList formals;
  int max_offset;
};


F_accessList F_AccessList(F_access head,F_accessList tail);
F_access InFrame(int offset);
F_access InReg(Temp_temp reg);
F_frame F_newFrame(Temp_label name,U_boolList formals);
F_access F_allocLocal(F_frame f,bool escape);
Temp_temp F_FP();
extern const int F_wordSize;
T_exp F_Exp(F_access f_access,T_exp framePtr);
T_exp F_externalCall(string s,T_expList args);

struct F_frag_{
  enum{F_stringFrag,F_progFrag}kind;
  union{
    struct{
      Temp_label label;
      string str;
    }stringg;
    struct{
      T_stm body;
      F_frame frame;
    }proc;
  }u;
};
struct F_fragList_{
  F_frag head;
  F_fragList tail;
};
F_frag F_StringFrag(Temp_label label,string str);
F_frag F_ProgFrag(T_stm body,F_frame frame);
F_fragList F_FragList(F_frag head,F_fragList tail);
