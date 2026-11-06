extern "C" {
int FUN_0023deb0(...);
int FUN_002467a0(...);
extern int DAT_004ea380[4];
extern int DAT_004ea5c0[4];
void FUN_00241210(int arg0, int arg1, void **arg2, int arg3, int arg4);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_00241210(int arg0, int arg1, void **arg2, int arg3, int arg4) {
    if (arg1 == 0) {
        FUN_002467a0(&DAT_004ea5c0[0], arg3, *(int *)((char *)(((DW4VC_88_0 *)(arg2))->vX()) + 28));
        return;
    }
    if (FUN_0023deb0(arg0, arg1, arg2, arg4) == 0) {
        FUN_002467a0(&DAT_004ea380[0], arg3, *(int *)((char *)(((DW4VC_88_0 *)(arg2))->vX()) + 28));
    }
}
