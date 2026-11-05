/* 0x003284d0 — FUN_003284d0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern "C" {
int FUN_002d6e60(...);
int FUN_002f89a0(...);
void *FUN_0032a100(...);
int FUN_0032a180(...);
int FUN_0032a1b0(...);
void *FUN_0032a1e0(...);
int List_InsertWords(...);
void FUN_0032a260(void);  /* code at 0x32a260, passed by address (was DAT_32a260; docs/engine/function-inventory.md) */
extern int DAT_004ff570[4];
void FUN_003284d0(void *arg0, int arg1);
}
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
void FUN_003284d0(void *arg0, int arg1) {
    void *sp3C;
    void *var_v0;

    if (((DW4VC_132_0 *)(((char *)(arg0) + 0)))->vX() != 0) {
        var_v0 = (void *)(FUN_0032a1e0(0xA8));
        if (var_v0 != 0) {
            var_v0 = (void *)(FUN_0032a100(var_v0));
        }
        sp3C = (void *)(var_v0);
        *(int *)((char *)(var_v0) + 0) = (int)((int) *(int *)((char *)(arg0) + 116));
        *(int *)((char *)(sp3C) + 4) = (int)((int) *(int *)((char *)(arg0) + 120));
        FUN_0032a180(sp3C, &DAT_004ff570[0]);
        FUN_0032a1b0(sp3C, FUN_002f89a0(arg0));
        List_InsertWords(arg1, FUN_002d6e60(arg1, &sp3C, FUN_0032a260), 1, &sp3C);
    }
}
