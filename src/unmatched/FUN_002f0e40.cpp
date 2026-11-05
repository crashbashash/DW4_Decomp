/* 0x002f0e40 - FUN_002f0e40. Sibling of FUN_002f1e30; the unsigned __int128 argument and the allocator-alias virtual call are written inline in the call (spills the 128-bit value like retail); alternate compiler. Verified byte-identical by tools/verify.py. */
extern "C" {
int FUN_002e2190(int *, int, int, int, unsigned __int128, int, int, int, long long, long long, long long, long long);
int FUN_002e2300(...);
int Memory_GetBufferSize(int);
void *Memory_GetCurrentContextAlias(...);
}
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v152(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void v268(int *, int, int); };
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual long long v108(void *); };
extern "C" int FUN_002f0e40(void *arg0, int arg1, int arg2, long long arg3, long long arg4, long long arg5, int arg6);
int FUN_002f0e40(void *arg0, int arg1, int arg2, long long arg3, long long arg4, long long arg5, int arg6) {
    int spD0[40];
    int v0;
    int s8;
    VM *o = (VM *)arg0;
    v0 = o->v212();
    if (v0 != 0) {
        s8 = Memory_GetBufferSize(v0);
        FUN_002e2190(spD0, 1, v0, s8, (unsigned short)o->v152(), arg2, 0, 0, arg3, arg4, arg5, ((VA *)Memory_GetCurrentContextAlias())->v108(arg0));
        o->v268(spD0, arg1, arg6 + 1);
        FUN_002e2300(spD0, -1);
    }
    return v0;
}
