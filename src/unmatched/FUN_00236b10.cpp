extern "C" {
int FUN_00236b70(...);
int FUN_002d7750(...);
void FUN_00236b10(void *arg0, void *arg1);
}
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
void FUN_00236b10(void *arg0, void *arg1) {
    int sp3C;

    if (FUN_00236b70() != 0) {
        ((DW4VC_96_0 *)(((char *)(arg1) + 0)))->vX();
        *(int *)((char *)(arg1) + 12) = 0;
        FUN_002d7750(&sp3C, *(int *)((char *)(arg0) + 8), arg1);
    }
}
