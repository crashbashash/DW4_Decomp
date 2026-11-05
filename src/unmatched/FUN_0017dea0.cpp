extern "C" {
int igObject_Destroy(int *);
void FUN_0017dea0(int *arg0, int *arg1, int arg2);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void vX(int); };
void FUN_0017dea0(int *arg0, int *arg1, int arg2) {
    int *old;
    int *slot;
    int idx;

    if (arg1 != 0) {
        arg1[1] = arg1[1] + 1;
    }
    idx = arg2 * 4;
    idx = idx + (int)arg0;
    slot = (int *)(idx + 240);
    old = (int *)*slot;
    if (old != 0) {
        old[1] = old[1] - 1;
        if ((old[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = (int)arg1;
    if (arg1 != 0) {
        ((Obj *)arg0)->vX(0);
    }
}
