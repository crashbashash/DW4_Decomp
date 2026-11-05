typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int FUN_001354b0();
int FUN_001648f0();
int FUN_00164970();
int FUN_00199450();
int FUN_00226990();
int ObjectRef_Destruct_00150eb0();
int igObject_InitHeader();
extern int DAT_00535160[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[13]; char b[52]; };
int beDataBase_GetVTable(void) {
    union U u;
    int temp_s5;

    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00535160[0]);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00535160[0]);
    FUN_00199450(&u.w[13], -1);
    FUN_00199450(&u.w[12], -1);
    FUN_00226990(&u.w[11], -1);
    FUN_00199450(&u.w[10], -1);
    FUN_001354b0(&u.w[9], -1);
    FUN_00199450(&u.w[8], -1);
    ObjectRef_Destruct_00150eb0(&u.w[7], -1);
    FUN_00199450(&u.w[6], -1);
    FUN_001648f0(&u.w[5], -1);
    FUN_00199450(&u.w[4], -1);
    FUN_00164970(&u.w[3], -1);
    FUN_00199450(&u.w[2], -1);
    return temp_s5;
}
