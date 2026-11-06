/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[48]; };
extern "C" {
int igObject_InitHeader(char *);
int FUN_0033dda0(char *, int);
int FUN_0033f5e0(char *, int);
extern int DAT_0053eae0[4];
extern void * DAT_00586dc8[4];
int beNDMWSaveCtrl_GetVTable(void);
}
int beNDMWSaveCtrl_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053eae0[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053eae0[0];
    FUN_0033dda0(ps, -1);
    FUN_0033f5e0(u.b, 0);
    return temp_s0;
}
