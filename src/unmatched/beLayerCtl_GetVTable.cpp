/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[48]; };
extern "C" {
int FUN_00343260(int *, int);
int FUN_0033f5e0(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053a940[4];
extern void * DAT_00586dc8[4];
int beLayerCtl_GetVTable(void);
}
int beLayerCtl_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053a940[0];
    p = (int *)&u.b[36];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053a940[0];
    FUN_00343260(p, -1);
    FUN_0033f5e0(u.b, 0);
    return temp_s0;
}
