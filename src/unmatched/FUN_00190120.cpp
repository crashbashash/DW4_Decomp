extern "C" {
int (*FUN_0018fb60(int))(void **, int);
void FUN_00190120(void **arg0, int arg1, int arg2);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_00190120(void **arg0, int arg1, int arg2) {
    int i;
    int (*fn)(void **, int);
    fn = (int (*)(void **, int))(FUN_0018fb60(((DW4VC_88_0 *)(arg0))->vX()));
    for (i = 0; i < arg2; i++) {
        fn(arg0, arg1 + i * 0xC);
    }
}
