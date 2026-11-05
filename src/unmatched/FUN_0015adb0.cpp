struct Rc { int vt; int rc; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();  virtual int vX(int); };
struct S0 { char pad8[8]; V *f8; int f12; int f16; int f20; int f24; };
extern "C" {
int igObject_Destroy(void *);
Rc *igObject_GetAllocator(S0 *);
int FUN_0015adb0(S0 *arg0, int arg1, int arg2, int arg3);
}
int FUN_0015adb0(S0 *arg0, int arg1, int arg2, int arg3) {
    int var_s1;
    Rc *temp_a0;
    V *temp_a0_2;
    Rc *temp_v0;

    if (arg0->f12 != 0) {
        return 0;
    }
    arg0->f16 = arg1;
    arg0->f20 = arg3;
    arg0->f24 = arg2;
    if (arg3 == 0) {
        var_s1 = arg0->f16 * 2;
    } else {
        var_s1 = arg0->f16 * 4;
    }
    if (arg0->f8 == 0) {
        temp_v0 = igObject_GetAllocator(arg0);
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = (Rc *)arg0->f8;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f8 = (V *)temp_v0;
    }
    temp_a0_2 = arg0->f8;
    arg0->f12 = temp_a0_2->vX(var_s1);
    return var_s1;
}
