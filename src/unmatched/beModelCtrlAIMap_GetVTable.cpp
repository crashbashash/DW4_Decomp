union U { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" {
int FUN_00131bc0(char *, int);
int FUN_00354490(int *, int);
int StringRef_Destruct_00130720(int *, int);
int igObject_InitHeader(char *);
extern int DAT_00537900[4];
extern void * DAT_00586dc8[4];
int beModelCtrlAIMap_GetVTable(void);
}
int beModelCtrlAIMap_GetVTable(void) {
    union U u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_00537900[0]);
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00537900[0]);
    StringRef_Destruct_00130720(&u.w[12], -1);
    StringRef_Destruct_00130720(&u.w[11], -1);
    FUN_00354490(&u.w[10], -1);
    FUN_00354490(&u.w[9], -1);
    FUN_00354490(&u.w[8], -1);
    FUN_00354490(&u.w[7], -1);
    FUN_00131bc0(u.b, 0);
    return temp_s5;
}
