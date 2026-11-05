/* 0x001682e0 — FUN_001682e0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern "C" {
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(); int rc; };
int FUN_00300f50(...);
int igObject_Destroy(...);
struct S { char pad[8]; O *f8; int f12; int f16; int f20; int f24; int f28; };
int FUN_001682e0(S *arg0, int arg1);
int FUN_001682e0(S *arg0, int arg1) {
    O *temp_a0;
    O *temp_a0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_a0->vX();
        temp_a0_2 = arg0->f8;
        if (temp_a0_2 != 0) {
            temp_a0_2->rc = temp_a0_2->rc - 1;
            if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->f8 = 0;
    }
    FUN_00300f50(arg0, arg0->f12);
    arg0->f12 = 0;
    FUN_00300f50(arg0, arg0->f16);
    arg0->f16 = 0;
    FUN_00300f50(arg0, arg0->f20);
    arg0->f20 = 0;
    arg0->f24 = 0;
    arg0->f28 = 0;
    return arg1;
}
}
