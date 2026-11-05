/* 0x00344b90 — beShadow01Info_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8).
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[48]; };
extern "C" {
int igObject_InitHeader(char *);
int FUN_00198210(char *, int);
int FUN_0033ec80(char *, int);
int FUN_00344c40(char *, int);
extern int DAT_00539140[4];
extern void * DAT_00586dc8[4];
int beShadow01Info_GetVTable(void);
}
int beShadow01Info_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00539140[0];
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[36] = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539140[0];
    FUN_00344c40(&u.b[36], -1);
    FUN_00198210(&u.b[32], -1);
    FUN_00198210(&u.b[28], -1);
    FUN_0033ec80(u.b, 0);
    return t;
}
