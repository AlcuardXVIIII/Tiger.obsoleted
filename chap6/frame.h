typedef struct F_frame_ *F_frame;

typedef struct F_access_ *F_access;

typedef struct F_accessList_ *F_accessList;

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
