/* 0x0033f4f0 - beWeapon_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" {
int FUN_0033f5e0(int *, int);
int FUN_0033f6d0(int *, int);
int igObject_InitHeader(char *);
extern int DAT_0053b630[4];
extern void * DAT_00586dc8[4];
int beWeapon_GetVTable(void);
}
int beWeapon_GetVTable(void) {
    union U u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&DAT_0053b630[0]);
    u.w[8] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053b630[0]);
    FUN_0033f6d0(&u.w[8], -1);
    FUN_0033f5e0(&u.w[0], 0);
    return temp_s0;
}
