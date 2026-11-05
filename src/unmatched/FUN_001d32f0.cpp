/* 0x001d32f0 - FUN_001d32f0. Recursive flag propagation over virtual children; the mask is applied in place on the argument. Verified byte-identical by tools/verify.py. */
struct S;
extern "C" { extern int DAT_0048da58[4]; void FUN_001d32f0(S *arg0, int arg1); }
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int c(); virtual S *g(int); };
struct S : V { char p[16]; int f20; };
void FUN_001d32f0(S *arg0, int arg1) {
    int temp_a0;
    int var_s0;

    temp_a0 = arg0->f20;
    arg1 = arg1 & DAT_0048da58[0];
    if (arg1 != (arg1 & temp_a0)) {
        var_s0 = 0;
        arg0->f20 = temp_a0 | arg1;
        while (var_s0 < arg0->c()) {
            FUN_001d32f0(arg0->g(var_s0), arg0->f20);
            var_s0 += 1;
        }
    }
}

