/* 0x00347870 — beSvPlatDataPS2_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8).
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[224]; };
extern "C" {
int igObject_InitHeader(char *);
int FUN_0014aa70(char *, int);
int FUN_00347150(char *, int);
int StringRef_Destruct_00130720(char *, int);
extern int DAT_00538bc0[4];
extern void * DAT_00586dc8[4];
int beSvPlatDataPS2_GetVTable(void);
}
int beSvPlatDataPS2_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[12] = 0;
    u.vt = (int)&DAT_00538bc0[0];
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[184] = 0;
    *(int *)&u.b[188] = 0;
    *(int *)&u.b[192] = 0;
    *(int *)&u.b[212] = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538bc0[0];
    FUN_0014aa70(&u.b[212], -1);
    StringRef_Destruct_00130720(&u.b[192], -1);
    StringRef_Destruct_00130720(&u.b[188], -1);
    StringRef_Destruct_00130720(&u.b[184], -1);
    StringRef_Destruct_00130720(&u.b[28], -1);
    StringRef_Destruct_00130720(&u.b[24], -1);
    FUN_00347150(u.b, 0);
    return t;
}
