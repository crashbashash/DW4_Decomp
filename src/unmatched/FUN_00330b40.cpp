extern "C" {
int __divdi3(...);
int __moddi3(...);
int __floatdidf(...);
int __adddf3(...);
int __divdf3(...);
int __floatsidf(...);
void FUN_00330b40(void **arg0);
}
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
void FUN_00330b40(void **arg0) {
    int temp_s0;
    int temp_s0_2;
    int temp_v0;

    temp_v0 = ((DW4VC_104_0 *)(arg0))->vX();
    temp_s0 = __floatdidf(__moddi3(temp_v0, 0x3B9ACA00));
    temp_s0_2 = __divdf3(temp_s0, __floatsidf(0x3B9ACA00));
    __adddf3(__floatdidf(__divdi3(temp_v0, 0x3B9ACA00)), temp_s0_2);
}
