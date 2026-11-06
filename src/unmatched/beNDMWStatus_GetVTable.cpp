/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[48]; };
extern "C" {
int FUN_003b2f30(char *, int);
int FUN_0033f5e0(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053e7c0[4];
extern void * DAT_00586dc8[4];
int beNDMWStatus_GetVTable(void);
}
int beNDMWStatus_GetVTable(void) {
    union U u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053e7c0[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053e7c0[0];
    FUN_003b2f30(ps, -1);
    FUN_0033f5e0(u.b, 0);
    return t;
}
