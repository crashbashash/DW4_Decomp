extern "C" {
extern int DAT_004fb418[4];
}
struct S { int v; S() {} };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual S vX(); };
extern "C" { extern VC *DAT_00587218[4]; }
struct F { char pad[136]; unsigned long long t; char pad2[16]; long long z; };
extern "C" S Gap__Core__igArenaMemoryPool__vfunc_106(void *arg1, int arg2, long long arg3) {
    F *f = (F *)arg1;
    if (f->z != 0) {
        S r;
        r.v = DAT_004fb418[0];
        return r;
    }
    long long d = (long long)(int)arg3;
    if ((unsigned long long)d < f->t) {
        f->t = f->t - d;
    } else {
        f->t = 0;
    }
    return (*DAT_00587218[0]).vX();
}
