/* 0x0036c6d0 — beAction2InfoRam_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8).
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[64]; };
extern "C" {
int igObject_InitHeader(char *);
int FUN_001a7a00(char *, int);
int FUN_001aa310(char *, int);
int FUN_0033e920(char *, int);
int FUN_0034c1b0(char *, int);
int FUN_0036c790(char *, int);
extern int DAT_00534350[4];
extern void * DAT_00586dc8[4];
int beAction2InfoRam_GetVTable(void);
}
int beAction2InfoRam_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[40] = 0;
    u.vt = (int)&DAT_00534350[0];
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00534350[0];
    FUN_0036c790(&u.b[56], -1);
    FUN_001aa310(&u.b[52], -1);
    FUN_001a7a00(&u.b[48], -1);
    FUN_0034c1b0(&u.b[44], -1);
    FUN_0033e920(u.b, 0);
    return t;
}
