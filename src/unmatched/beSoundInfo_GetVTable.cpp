union U { int vt; char b[48]; };
extern "C" {
int FUN_00199450(char *, int);
int FUN_0033ec80(char *, int);
int StringRef_Destruct_00130720(char *, int);
int igObject_InitHeader(char *);
extern int DAT_005393b0[4];
extern void * DAT_00586dc8[4];
int beSoundInfo_GetVTable(void);
}
int beSoundInfo_GetVTable(void) {
    union U u;
    int temp_s1;
    char *p1;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_005393b0[0];
    p1 = &u.b[28];
    *(int *)p1 = 0;
    *(int *)&u.b[32] = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005393b0[0];
    StringRef_Destruct_00130720(&u.b[32], -1);
    FUN_00199450(p1, -1);
    FUN_0033ec80(u.b, 0);
    return temp_s1;
}
