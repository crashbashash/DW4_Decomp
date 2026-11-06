/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[80]; };
extern "C" {
int FUN_0035d930(char *, int);
int FUN_0019e150(char *, int);
int igObject_InitHeader(char *);
extern int DAT_00536360[4];
extern void * DAT_00586dc8[4];
int beHitLandModelTraversal_GetVTable(void);
}
int beHitLandModelTraversal_GetVTable(void) {
    union U u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[36] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    u.vt = (int)&DAT_00536360[0];
    ps = &u.b[64];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00536360[0];
    FUN_0035d930(ps, -1);
    FUN_0019e150(u.b, 0);
    return t;
}
