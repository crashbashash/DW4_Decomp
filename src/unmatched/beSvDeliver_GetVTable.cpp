typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[17]; char b[68]; };
extern "C" {
int FUN_00349080(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int igObject_InitHeader(char *);
extern int DAT_005388b0[4];
extern void * DAT_00586dc8[4];
int beSvDeliver_GetVTable(void);
}
int beSvDeliver_GetVTable(void) {
    union U u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_005388b0[0]);
    u.w[3] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005388b0[0]);
    FUN_00349080(&u.w[16], -1);
    ObjectRef_Destruct_00150eb0(&u.w[15], -1);
    ObjectRef_Destruct_00150eb0(&u.w[14], -1);
    ObjectRef_Destruct_00150eb0(&u.w[13], -1);
    ObjectRef_Destruct_00150eb0(&u.w[12], -1);
    ObjectRef_Destruct_00150eb0(&u.w[3], -1);
    return temp_s5;
}
