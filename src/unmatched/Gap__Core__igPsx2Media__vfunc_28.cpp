extern "C" {
int FUN_0032e950(...);
int GetThreadId();
int SleepThread();
}
struct R { int code; };
class Q { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();  virtual R v29(); virtual void d30(); virtual R v31(int); };
struct M { char pad[16]; Q *q; };
extern "C" int Gap__Core__igPsx2Media__vfunc_28(M *arg0, int arg1, int arg2, int arg3) {
    int sp5C;
    arg0->q->v31(1);
    sp5C = 0;
    FUN_0032e950(arg0, arg1, arg2, arg3, 0, 3, GetThreadId(), &sp5C);
    arg0->q->v29();
    SleepThread();
    return sp5C;
}
