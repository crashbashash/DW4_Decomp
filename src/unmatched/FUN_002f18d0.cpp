/* FUN_002f18d0 */
extern "C" {
int FUN_002e2190(...);
int FUN_002e2300(...);
void **Memory_GetCurrentContextAlias(...);
int strlen(...);
int FUN_002f18d0(void **arg0, int arg1, int arg2, int arg3, int arg4, long long arg5, long long arg6, long long arg7, int arg_sp0);
}
class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
class DW4VC_244_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual int vX(); };
class DW4VC_268_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual int vX(void *, int, int); };
int FUN_002f18d0(void **arg0, int arg1, int arg2, int arg3, int arg4, long long arg5, long long arg6, long long arg7, int arg_sp0) {
    char spC0[160];
    int temp_v0;
    int temp_s1;
    void **temp_v0_2;

    temp_v0 = ((DW4VC_244_0 *)(arg0))->vX();
    if (temp_v0 != 0) {
        temp_s1 = strlen(arg1) + 1;
        temp_v0_2 = (void **)(Memory_GetCurrentContextAlias());
        FUN_002e2190(spC0, 1, temp_v0, temp_s1, arg2 & 0xFFFF, arg4, 0, 0, arg5, arg6, arg7, ((DW4VC_108_1 *)(temp_v0_2))->vX((int)(arg0)));
        ((DW4VC_268_3 *)(arg0))->vX(spC0, (int)(arg3), (int)(arg_sp0 + 1));
        FUN_002e2300(spC0, -1);
    }
    return temp_v0;
}
