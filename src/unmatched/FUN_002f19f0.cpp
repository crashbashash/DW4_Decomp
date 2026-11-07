extern "C" {
int FUN_002e2190(...);
int FUN_002e2300(...);
void *Memory_GetCurrentContextAlias();
extern int DAT_004fb410[4];
}
struct R { int w; R() {} R(const R &o) : w(o.w) {} };
class Ctx { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v108(void *); };
class F { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v152(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual R v248(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual int v268(void *, int, int); };
extern "C" void FUN_002f19f0(R *arg0, F *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10);
void FUN_002f19f0(R *arg0, F *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10) {
    char spB0[156];
    int first;
    int total;
    int flags;
    unsigned int i;
    Ctx *ctx;

    R res = arg1->v248();
    if ((arg2 != 0) && (arg3 != 0) && (arg4 != 0) && (res.w == DAT_004fb410[0])) {
        first = *arg4;
        total = 0;
        for (i = 0; i < (unsigned int) (arg2 & 0xFFFF); i++) {
            total += arg3[i];
        }
        flags = arg1->v152() & 0xFFFF;
        ctx = (Ctx *)(Memory_GetCurrentContextAlias());
        FUN_002e2190(spB0, 1, first, total, flags, arg6, 0, 0, arg7, arg_sp0, arg_sp8, ctx->v108(arg1));
        arg1->v268(spB0, arg5, arg_sp10 + 1);
        FUN_002e2300(spB0, -1);
    }
    *arg0 = res;
}
