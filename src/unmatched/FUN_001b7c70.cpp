extern "C" {
int FUN_001b9530(...);
int FUN_001d1550(...);
int FUN_001b7c70(void **arg0, void *arg1);
}
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
int FUN_001b7c70(void **arg0, void *arg1) {
    if (*(int *)((char *)(arg1) + 20) & 0x20) {
        return 0;
    }
    FUN_001d1550(arg1, ((DW4VC_104_0 *)(arg0))->vX());
    return FUN_001b9530(arg0, arg1);
}
