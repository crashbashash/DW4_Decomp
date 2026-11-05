/* 0x003b4e20 - beNDMWShopSelect01_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[28]; void *p[28]; char b[112]; };
extern "C" {
int FUN_003b4050(int *, int);
int igObject_InitHeader(char *);
extern int DAT_00540220[4];
extern void * DAT_00586dc8[4];
int beNDMWShopSelect01_GetVTable(void);
}
int beNDMWShopSelect01_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[20] = 0;
    u.w[27] = 0;
    u.w[0] = (int)(&DAT_00540220[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00540220[0]);
    FUN_003b4050(&u.w[0], 0);
    return temp_s0;
}
