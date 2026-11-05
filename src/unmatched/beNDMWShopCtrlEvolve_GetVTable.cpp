/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[112]; };
extern "C" {
int FUN_003b8980(int *, int);
int FUN_003b6770(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053fb40[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrlEvolve_GetVTable(void);
}
int beNDMWShopCtrlEvolve_GetVTable(void) {
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053fb40[0];
    p = (int *)&u.b[96];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053fb40[0];
    FUN_003b8980(p, -1);
    FUN_003b6770(u.b, 0);
    return temp_s0;
}
