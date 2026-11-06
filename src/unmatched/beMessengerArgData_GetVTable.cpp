struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_001354b0(int *, int);
int FUN_001374b0(int *, int);
int FUN_0014aa70(int *, int);
int FUN_00195190(int *, int);
int FUN_001998f0(int *, int);
int ObjectRef_Destruct_001c6460(int *, int);
int FUN_00226990(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_00536ca0[4];
extern void * DAT_00586dc8[4];
int beMessengerArgData_GetVTable(void);
}
int beMessengerArgData_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536ca0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536ca0[0];
    ObjectRef_Destruct_001c6460(&obj.w11, -1);
    FUN_0014aa70(&obj.w10, -1);
    FUN_001998f0(&obj.w9, -1);
    FUN_001374b0(&obj.w8, -1);
    FUN_00195190(&obj.w7, -1);
    FUN_001354b0(&obj.w6, -1);
    ObjectRef_Destruct_00150eb0(&obj.w5, -1);
    FUN_00226990(&obj.w4, -1);
    StringRef_Destruct_00130720(&obj.w3, -1);
    return t;
}
