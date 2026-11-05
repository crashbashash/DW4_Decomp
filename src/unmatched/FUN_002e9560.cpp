/* 0x2e9560 — FUN_002e9560. Verified byte-identical by tools/verify.py (wave3 sweep). */
extern "C" {
void **FUN_002d7e90(void *, int);
extern int DAT_004fb410[4];
void FUN_002e9560(int *arg0, void *arg1);
}
class DW4VC_148 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(void *); };
void FUN_002e9560(int *arg0, void *arg1) {
    int i;
    void **temp_v0;
    for (i = 0; i < *(int *)((char *)(arg1) + 8); i++) {
        temp_v0 = (void **)(FUN_002d7e90(arg1, i));
        ((DW4VC_148 *)(temp_v0))->vX(arg1);
    }
    *arg0 = DAT_004fb410[0];
}
