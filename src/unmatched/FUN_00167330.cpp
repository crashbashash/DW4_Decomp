extern "C" {
void **png_get_io_ptr(...);
void FUN_00167330(int dummy0, int arg1, int arg2);
}
class DW4VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
void FUN_00167330(int dummy0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(png_get_io_ptr());
    ((DW4VC_108_3 *)(temp_v0))->vX((int)(arg1), (int)(1), (int)(arg2));
}
