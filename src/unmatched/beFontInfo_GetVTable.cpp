union U { int vt; char b[32]; };
extern "C" {
int igObject_InitHeader(char *);
int FUN_00360f60(char *, int);
int FUN_0033ec80(char *, int);
extern int DAT_00535bd0[4];
extern void * DAT_00586dc8[4];
int beFontInfo_GetVTable(void);
}
int beFontInfo_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00535bd0[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00535bd0[0];
    FUN_00360f60(ps, -1);
    FUN_0033ec80(u.b, 0);
    return temp_s0;
}
