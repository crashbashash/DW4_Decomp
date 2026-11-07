extern "C" {
int FUN_002e2190(...);
int FUN_002e2300(...);
int Memory_GetBufferSize(...);
void *Memory_GetCurrentContextAlias();
}
class Ctx { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v108(void *); };
class F { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v152(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual int v232(int, int); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual int v268(void *, int, int); };
extern "C" int FUN_002f1410(F *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0);
int FUN_002f1410(F *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0) {
    char sp170[160];
    char spD0[160];
    int size;
    int flags;
    int flags2;
    Ctx *ctx;
    Ctx *ctx2;

    if (arg1 != 0) {
        size = Memory_GetBufferSize(arg1);
        FUN_002e2190(sp170, 3, arg1, size, (unsigned short)arg0->v152(), arg4, 0, 0, arg5, arg6, arg7, ((Ctx *)Memory_GetCurrentContextAlias())->v108(arg0));
        arg0->v268(sp170, arg3, arg_sp0 + 1);
        FUN_002e2300(sp170, -1);
    }
    arg1 = arg0->v232(arg1, arg2);
    if (arg1 != 0) {
        flags2 = arg0->v152() & 0xFFFF;
        ctx2 = (Ctx *)(Memory_GetCurrentContextAlias());
        FUN_002e2190(spD0, 1, arg1, arg2, flags2, arg4, 0, 0, arg5, arg6, arg7, ctx2->v108(arg0));
        arg0->v268(spD0, arg3, arg_sp0 + 1);
        FUN_002e2300(spD0, -1);
    }
    return arg1;
}
