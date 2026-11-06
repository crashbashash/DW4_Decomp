union U { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" {
int FUN_0033ec80(int *, int);
int StringRef_Destruct_00130720(int *, int);
int igObject_InitHeader(char *);
extern int DAT_00537c10[4];
extern void * DAT_00586dc8[4];
int beModelCtrlInfo_GetVTable(void);
}
int beModelCtrlInfo_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&DAT_00537c10[0]);
    u.w[7] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00537c10[0]);
    StringRef_Destruct_00130720(&u.w[7], -1);
    FUN_0033ec80(&u.w[0], 0);
    return temp_s0;
}
