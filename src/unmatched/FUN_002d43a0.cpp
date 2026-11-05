struct R { int v; R() {} R(const R &o) : v(o.v) {} };
struct VC {
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
 virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
 virtual void d24();
 virtual R vX1(int, char *, int, int *, char *, int, int *);
 virtual R vX2(int, char *, int, char *, int, int, long long, long long);
};
extern "C" void FUN_002d43a0(int *arg0, VC *arg1, int arg2, int arg3, long long arg4, long long arg5);
void FUN_002d43a0(int *arg0, VC *arg1, int arg2, int arg3, long long arg4, long long arg5) {
    char b1[256];
    char b2[256];
    int o1;
    int o2;
    R r1 = arg1->vX1(arg2, b1, 255, &o1, b2, 255, &o2);
    R r2 = arg1->vX2(arg2, b1, o1, b2, o2, arg3, arg4, arg5);
    *arg0 = r1.v;
}
