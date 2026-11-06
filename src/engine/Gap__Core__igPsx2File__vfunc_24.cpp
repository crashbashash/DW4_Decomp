extern "C" {
int FUN_0010f5b8(int);
int FUN_00300f50(void *, int);
void Gap__Core__igPsx2File__vfunc_24(int *arg0);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(); };
void Gap__Core__igPsx2File__vfunc_24(int *arg0) {
    if (arg0[6] >= 0) {
        ((Obj *)arg0)->vX();
        FUN_0010f5b8(arg0[6]);
        arg0[6] = -1;
        if (arg0[11] != 0) {
            FUN_00300f50(arg0, arg0[11]);
        }
        arg0[11] = 0;
        arg0[12] = 0;
        arg0[13] = 0;
        arg0[16] = 0;
    }
}
