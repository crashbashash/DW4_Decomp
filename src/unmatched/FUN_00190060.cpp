extern "C" {
int (*FUN_0018fad0(int, int))(void **, void **);
void FUN_00190060(void **arg0, void **arg1);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_00190060(void **arg0, void **arg1) {
    int temp_s0;

    temp_s0 = ((DW4VC_88_0 *)(arg0))->vX();
    FUN_0018fad0(temp_s0, ((DW4VC_88_0 *)(arg1))->vX())(arg0, arg1);
}
