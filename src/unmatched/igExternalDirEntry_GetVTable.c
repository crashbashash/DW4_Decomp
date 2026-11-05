/* 0x002c54a0 — igExternalDirEntry_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int igObject_InitHeader();
int FUN_0014f4e0();
int StringRef_Destruct_00130720();
extern int DAT_00530360[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[48]; };
int igExternalDirEntry_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_00530360[0];
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[40] = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00530360[0];
    StringRef_Destruct_00130720(&u.b[40], -1);
    StringRef_Destruct_00130720(&u.b[32], -1);
    StringRef_Destruct_00130720(&u.b[28], -1);
    FUN_0014f4e0(u.b, 0);
    return t;
}
