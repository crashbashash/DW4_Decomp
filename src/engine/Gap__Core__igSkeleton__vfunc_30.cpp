extern "C" {
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int *); };
int Gap__Core__igSkeleton__vfunc_30(VC *arg0, int arg1);
}
int Gap__Core__igSkeleton__vfunc_30(VC *arg0, int arg1) {
    int sp4C;
    int temp_v0;
    int var_s0;

    sp4C = 0;
    var_s0 = 0;
    do {
        temp_v0 = arg0->vX(arg1, &sp4C);
        if (temp_v0 != -1) {
            var_s0 += 1;
        }
    } while (temp_v0 != -1);
    return var_s0;
}
