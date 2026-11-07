union U { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" {
int FUN_001374b0(int *, int);
int FUN_00231030(char *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int igObject_InitHeader(char *);
extern int DAT_0053ba50[4];
extern void * DAT_00586dc8[4];
int beTargetObj_GetVTable(void);
}
int beTargetObj_GetVTable(void) {
    union U u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_0053ba50[0]);
    u.w[4] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053ba50[0]);
    FUN_001374b0(&u.w[6], -1);
    ObjectRef_Destruct_00150eb0(&u.w[5], -1);
    FUN_001374b0(&u.w[4], -1);
    FUN_00231030(u.b, 0);
    return temp_s2;
}
