/* 0x00378e80 — FUN_00378e80. m2c draft with dropped/gap parameters restored; verified
 * byte-identical by tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
extern int DAT_00589be8[4];
int FUN_00378e80(int dummy0, void *arg1);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
int FUN_00378e80(int dummy0, void *arg1) {
    int temp_s0;
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg1) + 28));
    temp_s0 = DAT_00589be8[0];
    return temp_s0 == ((DW4VC_88_0 *)(temp_a0))->vX();
}
