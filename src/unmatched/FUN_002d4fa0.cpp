extern "C" {
void FUN_002d4fa0(void *arg0, int arg1);
}
class V120 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(int); };
void FUN_002d4fa0(void *arg0, int arg1) {
    int lst;
    int i;
    for (i = 0; lst = *(int *)((char *)arg0 + 52), i < *(int *)(lst + 8); i++) {
        ((V120 *)(*(int *)(*(int *)(lst + 16) + i * 4)))->vX(arg1);
    }
}
