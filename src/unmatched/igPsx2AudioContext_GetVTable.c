/* 0x001431a0 — igPsx2AudioContext_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int igObject_InitHeader();
int FUN_00143250();
int FUN_001432d0();
int FUN_00143350();
extern int DAT_00524a80[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[64]; };
int igPsx2AudioContext_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524a80[0];
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[48] = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524a80[0];
    FUN_00143350(&u.b[48], -1);
    FUN_00143350(&u.b[20], -1);
    FUN_001432d0(&u.b[16], -1);
    FUN_00143250(&u.b[12], -1);
    return t;
}
