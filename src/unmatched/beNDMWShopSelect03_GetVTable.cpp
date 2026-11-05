/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[112]; };
extern "C" {
int FUN_003b4050(char *, int);
int igObject_InitHeader(char *);
extern int DAT_00540140[4];
extern void * DAT_00586dc8[4];
int beNDMWShopSelect03_GetVTable(void);
}
int beNDMWShopSelect03_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    *(int *)&u.b[80] = 0;
    *(int *)&u.b[108] = 0;
    u.vt = (int)&DAT_00540140[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540140[0];
    FUN_003b4050(u.b, 0);
    return temp_s0;
}
